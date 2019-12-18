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
struct inode {int /*<<< orphan*/  i_sb; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_JOURNAL (int /*<<< orphan*/ ) ; 
 int __add_jh (int /*<<< orphan*/ ,struct buffer_head*,int /*<<< orphan*/ ) ; 

int reiserfs_add_ordered_list(struct inode *inode, struct buffer_head *bh)
{
	return __add_jh(SB_JOURNAL(inode->i_sb), bh, 0);
}