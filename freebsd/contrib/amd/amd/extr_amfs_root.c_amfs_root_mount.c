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
typedef  scalar_t__ opaque_t ;
struct TYPE_3__ {int /*<<< orphan*/  mf_prfree; int /*<<< orphan*/  mf_info; scalar_t__ mf_private; int /*<<< orphan*/  mf_mount; } ;
typedef  TYPE_1__ mntfs ;
typedef  int /*<<< orphan*/  am_node ;

/* Variables and functions */
 scalar_t__ mapc_find (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mapc_free ; 
 int /*<<< orphan*/  pid_fsname ; 
 int /*<<< orphan*/  strealloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
amfs_root_mount(am_node *mp, mntfs *mf)
{
  mf->mf_mount = strealloc(mf->mf_mount, pid_fsname);
  mf->mf_private = (opaque_t) mapc_find(mf->mf_info, "", NULL, NULL);
  mf->mf_prfree = mapc_free;

  return 0;
}