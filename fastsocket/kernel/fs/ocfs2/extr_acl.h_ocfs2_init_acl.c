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
struct ocfs2_alloc_context {int dummy; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */

__attribute__((used)) static inline int ocfs2_init_acl(handle_t *handle,
				 struct inode *inode,
				 struct inode *dir,
				 struct buffer_head *di_bh,
				 struct buffer_head *dir_bh,
				 struct ocfs2_alloc_context *meta_ac,
				 struct ocfs2_alloc_context *data_ac)
{
	return 0;
}