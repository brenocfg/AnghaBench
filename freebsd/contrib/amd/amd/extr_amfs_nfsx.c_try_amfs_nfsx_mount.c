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
struct amfs_nfsx {int /*<<< orphan*/ * nx_mp; } ;
typedef  scalar_t__ opaque_t ;
struct TYPE_5__ {TYPE_1__* mf_ops; scalar_t__ mf_private; } ;
typedef  TYPE_2__ mntfs ;
typedef  int /*<<< orphan*/  am_node ;
struct TYPE_4__ {int (* mount_fs ) (int /*<<< orphan*/ *,TYPE_2__*) ;} ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int
try_amfs_nfsx_mount(opaque_t mv)
{
  mntfs *mf = (mntfs *) mv;
  struct amfs_nfsx *nx = (struct amfs_nfsx *) mf->mf_private;
  am_node *mp = nx->nx_mp;
  int error;

  error = mf->mf_ops->mount_fs(mp, mf);

  return error;
}