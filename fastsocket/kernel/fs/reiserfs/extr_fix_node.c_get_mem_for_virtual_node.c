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
struct tree_balance {int vn_buf_size; char* vn_buf; int /*<<< orphan*/  tb_path; int /*<<< orphan*/  tb_sb; } ;

/* Variables and functions */
 int CARRY_ON ; 
 scalar_t__ FILESYSTEM_CHANGED_TB (struct tree_balance*) ; 
 int GFP_ATOMIC ; 
 int GFP_NOFS ; 
 int /*<<< orphan*/  PATH_PLAST_BUFFER (int /*<<< orphan*/ ) ; 
 int REPEAT_SEARCH ; 
 int __GFP_NOWARN ; 
 int /*<<< orphan*/  free_buffers_in_tb (struct tree_balance*) ; 
 int get_virtual_node_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int) ; 
 int /*<<< orphan*/  schedule () ; 

__attribute__((used)) static int get_mem_for_virtual_node(struct tree_balance *tb)
{
	int check_fs = 0;
	int size;
	char *buf;

	size = get_virtual_node_size(tb->tb_sb, PATH_PLAST_BUFFER(tb->tb_path));

	if (size > tb->vn_buf_size) {
		/* we have to allocate more memory for virtual node */
		if (tb->vn_buf) {
			/* free memory allocated before */
			kfree(tb->vn_buf);
			/* this is not needed if kfree is atomic */
			check_fs = 1;
		}

		/* virtual node requires now more memory */
		tb->vn_buf_size = size;

		/* get memory for virtual item */
		buf = kmalloc(size, GFP_ATOMIC | __GFP_NOWARN);
		if (!buf) {
			/* getting memory with GFP_KERNEL priority may involve
			   balancing now (due to indirect_to_direct conversion on
			   dcache shrinking). So, release path and collected
			   resources here */
			free_buffers_in_tb(tb);
			buf = kmalloc(size, GFP_NOFS);
			if (!buf) {
				tb->vn_buf_size = 0;
			}
			tb->vn_buf = buf;
			schedule();
			return REPEAT_SEARCH;
		}

		tb->vn_buf = buf;
	}

	if (check_fs && FILESYSTEM_CHANGED_TB(tb))
		return REPEAT_SEARCH;

	return CARRY_ON;
}