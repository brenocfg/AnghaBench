#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int mf_flags; } ;
typedef  TYPE_4__ mntfs ;
struct TYPE_12__ {int am_flags; TYPE_2__* am_parent; int /*<<< orphan*/  am_ttl; int /*<<< orphan*/  am_path; TYPE_3__* am_al; } ;
typedef  TYPE_5__ am_node ;
struct TYPE_10__ {TYPE_4__* al_mnt; } ;
struct TYPE_8__ {int /*<<< orphan*/  na_mtime; } ;
struct TYPE_9__ {TYPE_1__ am_fattr; } ;

/* Variables and functions */
 int AMF_NOTIMEOUT ; 
 int AMF_ROOT ; 
 int /*<<< orphan*/  AMQ_UMNT_FAILED ; 
 int /*<<< orphan*/  EBUSY ; 
 int MFF_MOUNTING ; 
 int MFF_UNMOUNTING ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int /*<<< orphan*/  XLOG_WARNING ; 
 int /*<<< orphan*/  clocktime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  notify_child (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reschedule_timeout_mp () ; 

void
forcibly_timeout_mp(am_node *mp)
{
  mntfs *mf = mp->am_al->al_mnt;
  /*
   * Arrange to timeout this node
   */
  if (mf && ((mp->am_flags & AMF_ROOT) ||
	     (mf->mf_flags & (MFF_MOUNTING | MFF_UNMOUNTING)))) {
    /*
     * We aren't going to schedule a timeout, so we need to notify the
     * child here unless we are already unmounting, in which case that
     * process is responsible for notifying the child.
     */
    if (mf->mf_flags & MFF_UNMOUNTING)
      plog(XLOG_WARNING, "node %s is currently being unmounted, ignoring timeout request", mp->am_path);
    else {
      plog(XLOG_WARNING, "ignoring timeout request for active node %s", mp->am_path);
      notify_child(mp, AMQ_UMNT_FAILED, EBUSY, 0);
    }
  } else {
    plog(XLOG_INFO, "\"%s\" forcibly timed out", mp->am_path);
    mp->am_flags &= ~AMF_NOTIMEOUT;
    mp->am_ttl = clocktime(NULL);
    /*
     * Force mtime update of parent dir, to prevent DNLC/dcache from caching
     * the old entry, which could result in ESTALE errors, bad symlinks, and
     * more.
     */
    clocktime(&mp->am_parent->am_fattr.na_mtime);
    reschedule_timeout_mp();
  }
}