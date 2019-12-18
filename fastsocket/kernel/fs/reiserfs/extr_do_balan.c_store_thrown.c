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
struct tree_balance {int /*<<< orphan*/  tb_sb; struct buffer_head** thrown; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (struct buffer_head**) ; 
 scalar_t__ buffer_dirty (struct buffer_head*) ; 
 int /*<<< orphan*/  get_bh (struct buffer_head*) ; 
 int /*<<< orphan*/  reiserfs_warning (int /*<<< orphan*/ ,char*,char*) ; 

__attribute__((used)) static void store_thrown(struct tree_balance *tb, struct buffer_head *bh)
{
	int i;

	if (buffer_dirty(bh))
		reiserfs_warning(tb->tb_sb, "reiserfs-12320",
				 "called with dirty buffer");
	for (i = 0; i < ARRAY_SIZE(tb->thrown); i++)
		if (!tb->thrown[i]) {
			tb->thrown[i] = bh;
			get_bh(bh);	/* free_thrown puts this */
			return;
		}
	reiserfs_warning(tb->tb_sb, "reiserfs-12321",
			 "too many thrown buffers");
}