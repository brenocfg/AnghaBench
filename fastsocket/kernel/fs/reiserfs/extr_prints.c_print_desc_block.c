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
struct reiserfs_journal_desc {int dummy; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  JOURNAL_DESC_MAGIC ; 
 int /*<<< orphan*/  get_desc_mount_id (struct reiserfs_journal_desc*) ; 
 int /*<<< orphan*/  get_desc_trans_id (struct reiserfs_journal_desc*) ; 
 int /*<<< orphan*/  get_desc_trans_len (struct reiserfs_journal_desc*) ; 
 int /*<<< orphan*/  get_journal_desc_magic (struct buffer_head*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printk (char*,unsigned long long,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int print_desc_block(struct buffer_head *bh)
{
	struct reiserfs_journal_desc *desc;

	if (memcmp(get_journal_desc_magic(bh), JOURNAL_DESC_MAGIC, 8))
		return 1;

	desc = (struct reiserfs_journal_desc *)(bh->b_data);
	printk("Desc block %llu (j_trans_id %d, j_mount_id %d, j_len %d)",
	       (unsigned long long)bh->b_blocknr, get_desc_trans_id(desc),
	       get_desc_mount_id(desc), get_desc_trans_len(desc));

	return 0;
}