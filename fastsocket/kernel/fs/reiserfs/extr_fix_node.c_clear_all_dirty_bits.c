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
struct super_block {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int reiserfs_prepare_for_journal (struct super_block*,struct buffer_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int clear_all_dirty_bits(struct super_block *s, struct buffer_head *bh)
{
	return reiserfs_prepare_for_journal(s, bh, 0);
}