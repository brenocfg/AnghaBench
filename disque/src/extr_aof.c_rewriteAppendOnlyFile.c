#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct dictEntry {int dummy; } ;
typedef  char* sds ;
typedef  int /*<<< orphan*/  rio ;
typedef  int mstime_t ;
struct TYPE_5__ {scalar_t__ state; } ;
typedef  TYPE_1__ job ;
typedef  int /*<<< orphan*/  dictIterator ;
typedef  int /*<<< orphan*/  cmd ;
struct TYPE_6__ {char* aof_child_diff; int /*<<< orphan*/  aof_pipe_read_ack_from_parent; int /*<<< orphan*/  aof_pipe_write_ack_to_parent; int /*<<< orphan*/  aof_pipe_read_data_from_parent; int /*<<< orphan*/  jobs; scalar_t__ aof_rewrite_incremental_fsync; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  AE_READABLE ; 
 scalar_t__ ANET_OK ; 
 int /*<<< orphan*/  AOF_AUTOSYNC_BYTES ; 
 int C_ERR ; 
 int C_OK ; 
 scalar_t__ EOF ; 
 scalar_t__ JOB_STATE_ACTIVE ; 
 scalar_t__ JOB_STATE_QUEUED ; 
 int /*<<< orphan*/  LL_NOTICE ; 
 int /*<<< orphan*/  LL_WARNING ; 
 int /*<<< orphan*/  SER_STORAGE ; 
 scalar_t__ aeWait (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ anetNonBlock (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aofReadDiffFromParent () ; 
 int /*<<< orphan*/ * dictGetIterator (int /*<<< orphan*/ ) ; 
 TYPE_1__* dictGetKey (struct dictEntry*) ; 
 struct dictEntry* dictNext (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dictReleaseIterator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ fclose (int /*<<< orphan*/ *) ; 
 scalar_t__ fflush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fileno (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int fsync (int /*<<< orphan*/ ) ; 
 scalar_t__ getpid () ; 
 int mstime () ; 
 int rename (char*,char*) ; 
 int /*<<< orphan*/  rioInitWithFile (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rioSetAutoSync (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rioWrite (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ rioWriteBulkString (int /*<<< orphan*/ *,char*,int) ; 
 char* sdsempty () ; 
 int /*<<< orphan*/  sdsfree (char*) ; 
 int sdslen (char*) ; 
 char* serializeJob (char*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_2__ server ; 
 int /*<<< orphan*/  serverLog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 double strerror (int /*<<< orphan*/ ) ; 
 int syncRead (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int write (int /*<<< orphan*/ ,char*,int) ; 

int rewriteAppendOnlyFile(char *filename, int background) {
    dictIterator *di = NULL;
    rio aof;
    FILE *fp;
    char tmpfile[256];
    char byte;

    /* Note that we have to use a different temp name here compared to the
     * one used by rewriteAppendOnlyFileBackground() function. */
    snprintf(tmpfile,256,"temp-rewriteaof-%d.aof", (int) getpid());
    fp = fopen(tmpfile,"w");
    if (!fp) {
        serverLog(LL_WARNING, "Opening the temp file for AOF rewrite in rewriteAppendOnlyFile(): %s", strerror(errno));
        return C_ERR;
    }

    if (background) server.aof_child_diff = sdsempty();
    rioInitWithFile(&aof,fp);
    if (server.aof_rewrite_incremental_fsync)
        rioSetAutoSync(&aof,AOF_AUTOSYNC_BYTES);

    /* Rerwite jobs that are in interesting states: active or queued.
     * ad LOADJOB commands. */
    di = dictGetIterator(server.jobs);
    struct dictEntry *de;
    while((de = dictNext(di)) != NULL) {
        job *job = dictGetKey(de);
        if (job->state != JOB_STATE_ACTIVE &&
            job->state != JOB_STATE_QUEUED) continue;

        char cmd[] = "*2\r\n$7\r\nLOADJOB\r\n";
        sds serialized = serializeJob(sdsempty(),job,SER_STORAGE);
        if (rioWrite(&aof,cmd,sizeof(cmd)-1) == 0) goto werr;
        if (rioWriteBulkString(&aof,serialized,sdslen(serialized)) == 0)
            goto werr;
        sdsfree(serialized);
    }
    dictReleaseIterator(di);
    di = NULL; /* Don't free it at end. */

    /* If this is a synchronous rewrite, skip all the child-parent
     * handshake about the difference buffer. */
    if (!background) goto flush_and_rename;

    /* Do an initial slow fsync here while the parent is still sending
     * data, in order to make the next final fsync faster. */
    if (fflush(fp) == EOF) goto werr;
    if (fsync(fileno(fp)) == -1) goto werr;

    /* Read again a few times to get more data from the parent.
     * We can't read forever (the server may receive data from clients
     * faster than it is able to send data to the child), so we try to read
     * some more data in a loop as soon as there is a good chance more data
     * will come. If it looks like we are wasting time, we abort (this
     * happens after 20 ms without new data). */
    int nodata = 0;
    mstime_t start = mstime();
    while(mstime()-start < 1000 && nodata < 20) {
        if (aeWait(server.aof_pipe_read_data_from_parent, AE_READABLE, 1) <= 0)
        {
            nodata++;
            continue;
        }
        nodata = 0; /* Start counting from zero, we stop on N *contiguous*
                       timeouts. */
        aofReadDiffFromParent();
    }

    /* Ask the master to stop sending diffs. */
    if (write(server.aof_pipe_write_ack_to_parent,"!",1) != 1) goto werr;
    if (anetNonBlock(NULL,server.aof_pipe_read_ack_from_parent) != ANET_OK)
        goto werr;
    /* We read the ACK from the server using a 10 seconds timeout. Normally
     * it should reply ASAP, but just in case we lose its reply, we are sure
     * the child will eventually get terminated. */
    if (syncRead(server.aof_pipe_read_ack_from_parent,&byte,1,5000) != 1 ||
        byte != '!') goto werr;
    serverLog(LL_NOTICE,"Parent agreed to stop sending diffs. Finalizing AOF...");

    /* Read the final diff if any. */
    aofReadDiffFromParent();

    /* Write the received diff to the file. */
    serverLog(LL_NOTICE,
        "Concatenating %.2f MB of AOF diff received from parent.",
        (double) sdslen(server.aof_child_diff) / (1024*1024));
    if (rioWrite(&aof,server.aof_child_diff,sdslen(server.aof_child_diff)) == 0)
        goto werr;

flush_and_rename:
    /* Make sure data will not remain on the OS's output buffers */
    if (fflush(fp) == EOF) goto werr;
    if (fsync(fileno(fp)) == -1) goto werr;
    if (fclose(fp) == EOF) goto werr;

    /* Use RENAME to make sure the AOF file is changed atomically only
     * if the generate AOF file is ok. */
    if (rename(tmpfile,filename) == -1) {
        serverLog(LL_WARNING,"Error moving temp append only file on the final destination: %s", strerror(errno));
        unlink(tmpfile);
        return C_ERR;
    }
    serverLog(LL_NOTICE,"SYNC append only file rewrite performed");
    return C_OK;

werr:
    serverLog(LL_WARNING,"Write error writing append only file on disk: %s", strerror(errno));
    fclose(fp);
    unlink(tmpfile);
    if (di) dictReleaseIterator(di);
    return C_ERR;
}