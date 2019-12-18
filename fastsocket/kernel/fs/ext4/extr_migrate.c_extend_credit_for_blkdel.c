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
typedef  int /*<<< orphan*/  handle_t ;

/* Variables and functions */
 int EXT4_MAXQUOTAS_TRANS_BLOCKS (int /*<<< orphan*/ ) ; 
 scalar_t__ EXT4_RESERVE_TRANS_BLOCKS ; 
 scalar_t__ ext4_handle_has_enough_credits (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ ext4_journal_extend (int /*<<< orphan*/ *,int) ; 
 int ext4_journal_restart (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int extend_credit_for_blkdel(handle_t *handle, struct inode *inode)
{
	int retval = 0, needed;

	if (ext4_handle_has_enough_credits(handle, EXT4_RESERVE_TRANS_BLOCKS+1))
		return 0;
	/*
	 * We are freeing a blocks. During this we touch
	 * superblock, group descriptor and block bitmap.
	 * So allocate a credit of 3. We may update
	 * quota (user and group).
	 */
	needed = 3 + EXT4_MAXQUOTAS_TRANS_BLOCKS(inode->i_sb);

	if (ext4_journal_extend(handle, needed) != 0)
		retval = ext4_journal_restart(handle, needed);

	return retval;
}