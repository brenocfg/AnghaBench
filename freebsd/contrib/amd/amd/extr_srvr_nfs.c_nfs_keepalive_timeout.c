#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* voidp ;
struct TYPE_12__ {int np_ping; scalar_t__ np_ttl; int np_error; int /*<<< orphan*/  np_xid; } ;
typedef  TYPE_2__ nfs_private ;
struct TYPE_11__ {int fs_flags; int /*<<< orphan*/  fs_host; scalar_t__ fs_private; } ;
typedef  TYPE_1__ fserver ;

/* Variables and functions */
 int FSF_DOWN ; 
 int FSF_VALID ; 
 int FSF_WANT ; 
 scalar_t__ FSRV_ISUP (TYPE_1__*) ; 
 int /*<<< orphan*/  MAX_ALLOWED_PINGS ; 
 int /*<<< orphan*/  XID_ALLOC () ; 
 int /*<<< orphan*/  check_fs_addr_change (TYPE_1__*) ; 
 scalar_t__ clocktime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlog (char*,...) ; 
 int /*<<< orphan*/  flush_nfs_fhandle_cache (TYPE_1__*) ; 
 int /*<<< orphan*/  nfs_keepalive (TYPE_1__*) ; 
 int /*<<< orphan*/  srvrlog (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  wakeup_srvr (TYPE_1__*) ; 

__attribute__((used)) static void
nfs_keepalive_timeout(voidp v)
{
  fserver *fs = v;
  nfs_private *np = (nfs_private *) fs->fs_private;

  /*
   * Another ping has failed
   */
  np->np_ping++;
  if (np->np_ping > 1)
    srvrlog(fs, "not responding");

  /*
   * Not known to be up any longer
   */
  if (FSRV_ISUP(fs))
    fs->fs_flags &= ~FSF_VALID;

  /*
   * If ttl has expired then guess that it is dead
   */
  if (np->np_ttl < clocktime(NULL)) {
    int oflags = fs->fs_flags;
    dlog("ttl has expired");
    if ((fs->fs_flags & FSF_DOWN) == 0) {
      /*
       * Server was up, but is now down.
       */
      srvrlog(fs, "is down");
      fs->fs_flags |= FSF_DOWN | FSF_VALID;
      /*
       * Since the server is down, the portmap
       * information may now be wrong, so it
       * must be flushed from the local cache
       */
      flush_nfs_fhandle_cache(fs);
      np->np_error = -1;
      check_fs_addr_change(fs); /* check if IP addr of fserver changed */
    } else {
      /*
       * Known to be down
       */
      if ((fs->fs_flags & FSF_VALID) == 0)
	srvrlog(fs, "starts down");
      fs->fs_flags |= FSF_VALID;
    }
    if (oflags != fs->fs_flags && (fs->fs_flags & FSF_WANT))
      wakeup_srvr(fs);
    /*
     * Reset failed ping count
     */
    np->np_ping = 0;
  } else {
    if (np->np_ping > 1)
      dlog("%d pings to %s failed - at most %d allowed", np->np_ping, fs->fs_host, MAX_ALLOWED_PINGS);
  }

  /*
   * New RPC xid, so any late responses to the previous ping
   * get ignored...
   */
  np->np_xid = XID_ALLOC();

  /*
   * Run keepalive again
   */
  nfs_keepalive(fs);
}