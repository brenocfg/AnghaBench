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
struct tree_balance {struct buffer_head** used; struct buffer_head** FEB; int /*<<< orphan*/  tb_sb; } ;
struct buffer_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int MAX_FEB_SIZE ; 
 int /*<<< orphan*/  buffer_info_init_bh (struct tree_balance*,struct buffer_info*,struct buffer_head*) ; 
 int /*<<< orphan*/  make_empty_node (struct buffer_info*) ; 
 int /*<<< orphan*/  reiserfs_panic (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  set_buffer_uptodate (struct buffer_head*) ; 

struct buffer_head *get_FEB(struct tree_balance *tb)
{
	int i;
	struct buffer_info bi;

	for (i = 0; i < MAX_FEB_SIZE; i++)
		if (tb->FEB[i] != NULL)
			break;

	if (i == MAX_FEB_SIZE)
		reiserfs_panic(tb->tb_sb, "vs-12300", "FEB list is empty");

	buffer_info_init_bh(tb, &bi, tb->FEB[i]);
	make_empty_node(&bi);
	set_buffer_uptodate(tb->FEB[i]);
	tb->used[i] = tb->FEB[i];
	tb->FEB[i] = NULL;

	return tb->used[i];
}