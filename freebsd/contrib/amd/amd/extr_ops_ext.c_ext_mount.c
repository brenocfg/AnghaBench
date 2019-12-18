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
struct TYPE_3__ {int mf_flags; int /*<<< orphan*/  mf_mopts; int /*<<< orphan*/  mf_info; int /*<<< orphan*/  mf_mount; } ;
typedef  TYPE_1__ mntfs ;
typedef  int /*<<< orphan*/  am_node ;

/* Variables and functions */
 int MFF_ON_AUTOFS ; 
 int /*<<< orphan*/  XLOG_ERROR ; 
 int errno ; 
 int mount_ext (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,char const*) ; 
 int /*<<< orphan*/  plog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
ext_mount(am_node *am, mntfs *mf, char *mount_type,
  const char *mnttab_type)
{
  int on_autofs = mf->mf_flags & MFF_ON_AUTOFS;
  int error;

  error = mount_ext(mf->mf_mount, mf->mf_info, mf->mf_mopts, on_autofs,
      mount_type, mnttab_type);
  if (error) {
    errno = error;
    plog(XLOG_ERROR, "mount_ext: %m");
    return error;
  }

  return 0;
}