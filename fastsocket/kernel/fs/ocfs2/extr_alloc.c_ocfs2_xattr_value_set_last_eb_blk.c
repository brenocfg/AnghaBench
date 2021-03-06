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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_xattr_value_buf {TYPE_1__* vb_xv; } ;
struct ocfs2_extent_tree {struct ocfs2_xattr_value_buf* et_object; } ;
struct TYPE_2__ {int /*<<< orphan*/  xr_last_eb_blk; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ocfs2_xattr_value_set_last_eb_blk(struct ocfs2_extent_tree *et,
					      u64 blkno)
{
	struct ocfs2_xattr_value_buf *vb = et->et_object;

	vb->vb_xv->xr_last_eb_blk = cpu_to_le64(blkno);
}