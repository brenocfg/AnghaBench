#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int mf_flags; int /*<<< orphan*/  mf_mopts; TYPE_1__* mf_fo; int /*<<< orphan*/  mf_mount; } ;
typedef  TYPE_2__ mntfs ;
typedef  int /*<<< orphan*/  am_node ;
struct TYPE_4__ {int /*<<< orphan*/  opt_cachedir; int /*<<< orphan*/  opt_rfs; } ;

/* Variables and functions */
 int ESRCH ; 
 int MFF_ON_AUTOFS ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int errno ; 
 int mount_cachefs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
cachefs_mount(am_node *am, mntfs *mf)
{
  int on_autofs = mf->mf_flags & MFF_ON_AUTOFS;
  int error;

  error = mount_cachefs(mf->mf_mount,
			mf->mf_fo->opt_rfs,
			mf->mf_fo->opt_cachedir,
			mf->mf_mopts,
			on_autofs);
  if (error) {
    errno = error;
    /* according to Solaris, if errno==ESRCH, "options to not match" */
    if (error == ESRCH)
      plog(XLOG_ERROR, "mount_cachefs: options to no match: %m");
    else
      plog(XLOG_ERROR, "mount_cachefs: %m");
    return error;
  }

  return 0;
}