#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ time_t ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  mstime_t ;
struct TYPE_2__ {scalar_t__ aof_fsync; scalar_t__ aof_flush_postponed_start; scalar_t__ unixtime; int aof_child_pid; int aof_current_size; scalar_t__ aof_last_write_status; scalar_t__ aof_last_fsync; int /*<<< orphan*/  aof_fd; scalar_t__ aof_no_fsync_on_rewrite; int /*<<< orphan*/  aof_buf; int /*<<< orphan*/  aof_last_write_errno; int /*<<< orphan*/  aof_delayed_fsync; } ;

/* Variables and functions */
 scalar_t__ AOF_FSYNC_ALWAYS ; 
 scalar_t__ AOF_FSYNC_EVERYSEC ; 
 scalar_t__ AOF_WRITE_LOG_ERROR_RATE ; 
 int /*<<< orphan*/  BIO_AOF_FSYNC ; 
 scalar_t__ C_ERR ; 
 scalar_t__ C_OK ; 
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  aof_background_fsync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aof_fsync (int /*<<< orphan*/ ) ; 
 scalar_t__ bioPendingJobsOfType (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  exit (int) ; 
 int ftruncate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  latencyAddSampleIfNeeded (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  latencyEndMonitor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  latencyStartMonitor (int /*<<< orphan*/ ) ; 
 int sdsavail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsclear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsempty () ; 
 int /*<<< orphan*/  sdsfree (int /*<<< orphan*/ ) ; 
 int sdslen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sdsrange (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void flushAppendOnlyFile(int force) {
    ssize_t nwritten;
    int sync_in_progress = 0;
    mstime_t latency;

    if (sdslen(server.aof_buf) == 0) return;

    if (server.aof_fsync == AOF_FSYNC_EVERYSEC)
        sync_in_progress = bioPendingJobsOfType(BIO_AOF_FSYNC) != 0;

    if (server.aof_fsync == AOF_FSYNC_EVERYSEC && !force) {
        /* With this append fsync policy we do background fsyncing.
         * If the fsync is still in progress we can try to delay
         * the write for a couple of seconds. */
        if (sync_in_progress) {
            if (server.aof_flush_postponed_start == 0) {
                /* No previous write postponing, remember that we are
                 * postponing the flush and return. */
                server.aof_flush_postponed_start = server.unixtime;
                return;
            } else if (server.unixtime - server.aof_flush_postponed_start < 2) {
                /* We were already waiting for fsync to finish, but for less
                 * than two seconds this is still ok. Postpone again. */
                return;
            }
            /* Otherwise fall trough, and go write since we can't wait
             * over two seconds. */
            server.aof_delayed_fsync++;
            serverLog(LL_NOTICE,"Asynchronous AOF fsync is taking too long (disk is busy?). Writing the AOF buffer without waiting for fsync to complete, this may slow down Disque.");
        }
    }
    /* We want to perform a single write. This should be guaranteed atomic
     * at least if the filesystem we are writing is a real physical one.
     * While this will save us against the server being killed I don't think
     * there is much to do about the whole server stopping for power problems
     * or alike */

    latencyStartMonitor(latency);
    nwritten = write(server.aof_fd,server.aof_buf,sdslen(server.aof_buf));
    latencyEndMonitor(latency);
    /* We want to capture different events for delayed writes:
     * when the delay happens with a pending fsync, or with a saving child
     * active, and when the above two conditions are missing.
     * We also use an additional event name to save all samples which is
     * useful for graphing / monitoring purposes. */
    if (sync_in_progress) {
        latencyAddSampleIfNeeded("aof-write-pending-fsync",latency);
    } else if (server.aof_child_pid != -1) {
        latencyAddSampleIfNeeded("aof-write-active-child",latency);
    } else {
        latencyAddSampleIfNeeded("aof-write-alone",latency);
    }
    latencyAddSampleIfNeeded("aof-write",latency);

    /* We performed the write so reset the postponed flush sentinel to zero. */
    server.aof_flush_postponed_start = 0;

    if (nwritten != (signed)sdslen(server.aof_buf)) {
        static time_t last_write_error_log = 0;
        int can_log = 0;

        /* Limit logging rate to 1 line per AOF_WRITE_LOG_ERROR_RATE seconds. */
        if ((server.unixtime - last_write_error_log) > AOF_WRITE_LOG_ERROR_RATE) {
            can_log = 1;
            last_write_error_log = server.unixtime;
        }

        /* Log the AOF write error and record the error code. */
        if (nwritten == -1) {
            if (can_log) {
                serverLog(LL_WARNING,"Error writing to the AOF file: %s",
                    strerror(errno));
                server.aof_last_write_errno = errno;
            }
        } else {
            if (can_log) {
                serverLog(LL_WARNING,"Short write while writing to "
                                       "the AOF file: (nwritten=%lld, "
                                       "expected=%lld)",
                                       (long long)nwritten,
                                       (long long)sdslen(server.aof_buf));
            }

            if (ftruncate(server.aof_fd, server.aof_current_size) == -1) {
                if (can_log) {
                    serverLog(LL_WARNING, "Could not remove short write "
                             "from the append-only file.  Disque may refuse "
                             "to load the AOF the next time it starts.  "
                             "ftruncate: %s", strerror(errno));
                }
            } else {
                /* If the ftruncate() succeeded we can set nwritten to
                 * -1 since there is no longer partial data into the AOF. */
                nwritten = -1;
            }
            server.aof_last_write_errno = ENOSPC;
        }

        /* Handle the AOF write error. */
        if (server.aof_fsync == AOF_FSYNC_ALWAYS) {
            /* We can't recover when the fsync policy is ALWAYS since the
             * reply for the client is already in the output buffers, and we
             * have the contract with the user that on acknowledged write data
             * is synced on disk. */
            serverLog(LL_WARNING,"Can't recover from AOF write error when the AOF fsync policy is 'always'. Exiting...");
            exit(1);
        } else {
            /* Recover from failed write leaving data into the buffer. However
             * set an error to stop accepting writes as long as the error
             * condition is not cleared. */
            server.aof_last_write_status = C_ERR;

            /* Trim the sds buffer if there was a partial write, and there
             * was no way to undo it with ftruncate(2). */
            if (nwritten > 0) {
                server.aof_current_size += nwritten;
                sdsrange(server.aof_buf,nwritten,-1);
            }
            return; /* We'll try again on the next call... */
        }
    } else {
        /* Successful write(2). If AOF was in error state, restore the
         * OK state and log the event. */
        if (server.aof_last_write_status == C_ERR) {
            serverLog(LL_WARNING,
                "AOF write error looks solved, Disque can write again.");
            server.aof_last_write_status = C_OK;
        }
    }
    server.aof_current_size += nwritten;

    /* Re-use AOF buffer when it is small enough. The maximum comes from the
     * arena size of 4k minus some overhead (but is otherwise arbitrary). */
    if ((sdslen(server.aof_buf)+sdsavail(server.aof_buf)) < 4000) {
        sdsclear(server.aof_buf);
    } else {
        sdsfree(server.aof_buf);
        server.aof_buf = sdsempty();
    }

    /* Don't fsync if no-appendfsync-on-rewrite is set to yes and there are
     * children doing I/O in the background. */
    if (server.aof_no_fsync_on_rewrite && server.aof_child_pid != -1)
        return;

    /* Perform the fsync if needed. */
    if (server.aof_fsync == AOF_FSYNC_ALWAYS) {
        /* aof_fsync is defined as fdatasync() for Linux in order to avoid
         * flushing metadata. */
        latencyStartMonitor(latency);
        aof_fsync(server.aof_fd); /* Let's try to get this data on the disk */
        latencyEndMonitor(latency);
        latencyAddSampleIfNeeded("aof-fsync-always",latency);
        server.aof_last_fsync = server.unixtime;
    } else if ((server.aof_fsync == AOF_FSYNC_EVERYSEC &&
                server.unixtime > server.aof_last_fsync)) {
        if (!sync_in_progress) aof_background_fsync(server.aof_fd);
        server.aof_last_fsync = server.unixtime;
    }
}