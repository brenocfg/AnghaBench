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
struct inode {int dummy; } ;
typedef  int /*<<< orphan*/  loff_t ;
typedef  int /*<<< orphan*/  filldir_t ;
struct TYPE_2__ {int ip_dyn_features; } ;

/* Variables and functions */
 TYPE_1__* OCFS2_I (struct inode*) ; 
 int OCFS2_INLINE_DATA_FL ; 
 int ocfs2_dir_foreach_blk_el (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 
 int ocfs2_dir_foreach_blk_id (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int ocfs2_dir_foreach_blk(struct inode *inode, u64 *f_version,
				 loff_t *f_pos, void *priv, filldir_t filldir,
				 int *filldir_err)
{
	if (OCFS2_I(inode)->ip_dyn_features & OCFS2_INLINE_DATA_FL)
		return ocfs2_dir_foreach_blk_id(inode, f_version, f_pos, priv,
						filldir, filldir_err);

	return ocfs2_dir_foreach_blk_el(inode, f_version, f_pos, priv, filldir,
					filldir_err);
}