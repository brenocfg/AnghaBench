#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct ocfs2_xattr_value_root {int /*<<< orphan*/  xr_list; } ;
struct ocfs2_cow_context {struct ocfs2_xattr_value_root* cow_object; struct inode* inode; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 int ocfs2_xattr_get_clusters (struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*) ; 

__attribute__((used)) static int ocfs2_xattr_value_get_clusters(struct ocfs2_cow_context *context,
					  u32 v_cluster, u32 *p_cluster,
					  u32 *num_clusters,
					  unsigned int *extent_flags)
{
	struct inode *inode = context->inode;
	struct ocfs2_xattr_value_root *xv = context->cow_object;

	return ocfs2_xattr_get_clusters(inode, v_cluster, p_cluster,
					num_clusters, &xv->xr_list,
					extent_flags);
}