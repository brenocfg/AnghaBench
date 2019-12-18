#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  voidp ;
struct TYPE_5__ {scalar_t__ fs_refc; int /*<<< orphan*/  fs_flags; scalar_t__ fs_cid; int /*<<< orphan*/  fs_host; } ;
typedef  TYPE_1__ fserver ;

/* Variables and functions */
 int AM_TTL ; 
 int /*<<< orphan*/  FSF_DOWN ; 
 int /*<<< orphan*/  FSF_PINGING ; 
 int /*<<< orphan*/  FSF_VALID ; 
 scalar_t__ FSRV_ERROR (TYPE_1__*) ; 
 scalar_t__ FSRV_ISDOWN (TYPE_1__*) ; 
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ timeout (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout_srvr ; 
 int /*<<< orphan*/  untimeout (scalar_t__) ; 

void
free_srvr(fserver *fs)
{
  if (--fs->fs_refc == 0) {
    /*
     * The reference count is now zero,
     * so arrange for this node to be
     * removed in AM_TTL seconds if no
     * other mntfs is referencing it.
     */
    int ttl = (FSRV_ERROR(fs) || FSRV_ISDOWN(fs)) ? 19 : AM_TTL;

    dlog("Last hard reference to file server %s - will timeout in %ds", fs->fs_host, ttl);
    if (fs->fs_cid) {
      untimeout(fs->fs_cid);
      /*
       * Turn off pinging - XXX
       */
      fs->fs_flags &= ~FSF_PINGING;
    }

    /*
     * Keep structure lying around for a while
     */
    fs->fs_cid = timeout(ttl, timeout_srvr, (voidp) fs);

    /*
     * Mark the fileserver down and invalid again
     */
    fs->fs_flags &= ~FSF_VALID;
    fs->fs_flags |= FSF_DOWN;
  }
}