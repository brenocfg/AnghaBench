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
struct reiserfs_journal_list {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {unsigned int i_trans_id; struct reiserfs_journal_list* i_jl; } ;

/* Variables and functions */
 TYPE_1__* REISERFS_I (struct inode*) ; 
 int __commit_trans_jl (struct inode*,unsigned int,struct reiserfs_journal_list*) ; 
 int /*<<< orphan*/  reiserfs_update_inode_transaction (struct inode*) ; 

int reiserfs_commit_for_inode(struct inode *inode)
{
	unsigned int id = REISERFS_I(inode)->i_trans_id;
	struct reiserfs_journal_list *jl = REISERFS_I(inode)->i_jl;

	/* for the whole inode, assume unset id means it was
	 * changed in the current transaction.  More conservative
	 */
	if (!id || !jl) {
		reiserfs_update_inode_transaction(inode);
		id = REISERFS_I(inode)->i_trans_id;
		/* jl will be updated in __commit_trans_jl */
	}

	return __commit_trans_jl(inode, id, jl);
}