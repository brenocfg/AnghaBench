#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct inode {int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_size; int /*<<< orphan*/  i_nlink; } ;
struct TYPE_5__ {struct super_block* j_private; } ;
typedef  TYPE_1__ journal_t ;

/* Variables and functions */
 scalar_t__ IS_ERR (struct inode*) ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 struct inode* ext3_iget (struct super_block*,unsigned int) ; 
 int /*<<< orphan*/  ext3_init_journal_params (struct super_block*,TYPE_1__*) ; 
 int /*<<< orphan*/  ext3_msg (struct super_block*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,struct inode*,int /*<<< orphan*/ ) ; 
 TYPE_1__* journal_init_inode (struct inode*) ; 
 int /*<<< orphan*/  make_bad_inode (struct inode*) ; 

__attribute__((used)) static journal_t *ext3_get_journal(struct super_block *sb,
				   unsigned int journal_inum)
{
	struct inode *journal_inode;
	journal_t *journal;

	/* First, test for the existence of a valid inode on disk.  Bad
	 * things happen if we iget() an unused inode, as the subsequent
	 * iput() will try to delete it. */

	journal_inode = ext3_iget(sb, journal_inum);
	if (IS_ERR(journal_inode)) {
		ext3_msg(sb, KERN_ERR, "error: no journal found");
		return NULL;
	}
	if (!journal_inode->i_nlink) {
		make_bad_inode(journal_inode);
		iput(journal_inode);
		ext3_msg(sb, KERN_ERR, "error: journal inode is deleted");
		return NULL;
	}

	jbd_debug(2, "Journal inode found at %p: %Ld bytes\n",
		  journal_inode, journal_inode->i_size);
	if (!S_ISREG(journal_inode->i_mode)) {
		ext3_msg(sb, KERN_ERR, "error: invalid journal inode");
		iput(journal_inode);
		return NULL;
	}

	journal = journal_init_inode(journal_inode);
	if (!journal) {
		ext3_msg(sb, KERN_ERR, "error: could not load journal inode");
		iput(journal_inode);
		return NULL;
	}
	journal->j_private = sb;
	ext3_init_journal_params(sb, journal);
	return journal;
}