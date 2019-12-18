#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct continuation {scalar_t__ start; int /*<<< orphan*/  retry; scalar_t__* al; TYPE_1__* mp; } ;
typedef  scalar_t__ opaque_t ;
struct TYPE_3__ {int /*<<< orphan*/  am_path; } ;
typedef  TYPE_1__ am_node ;

/* Variables and functions */
 scalar_t__ ALLOWED_MOUNT_TIME ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IN_PROGRESS (struct continuation*) ; 
 int /*<<< orphan*/  XLOG_INFO ; 
 int amfs_bgmount (struct continuation*) ; 
 scalar_t__ clocktime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dlog (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_continuation (struct continuation*) ; 
 int /*<<< orphan*/  new_ttl (TYPE_1__*) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reschedule_timeout_mp () ; 

__attribute__((used)) static void
amfs_retry(int rc, int term, opaque_t arg)
{
  struct continuation *cp = (struct continuation *) arg;
  am_node *mp = cp->mp;
  int error = 0;

  dlog("Commencing retry for mount of %s", mp->am_path);

  new_ttl(mp);

  if ((cp->start + ALLOWED_MOUNT_TIME) < clocktime(NULL)) {
    /*
     * The entire mount has timed out.  Set the error code and skip past all
     * the mntfs's so that amfs_bgmount will not have any more
     * ways to try the mount, thus causing an error.
     */
    plog(XLOG_INFO, "mount of \"%s\" has timed out", mp->am_path);
    error = ETIMEDOUT;
    while (*cp->al)
      cp->al++;
    /* explicitly forbid further retries after timeout */
    cp->retry = FALSE;
  }
  if (error || !IN_PROGRESS(cp))
    error = amfs_bgmount(cp);
  else
    /* Normally it's amfs_bgmount() which frees the continuation. However, if
     * the mount is already in progress and we're in amfs_retry() for another
     * node we don't try mounting the filesystem once again. Still, we have
     * to free the continuation as we won't get called again and thus would
     * leak the continuation structure and our am_loc references.
     */
    free_continuation(cp);

  reschedule_timeout_mp();
}