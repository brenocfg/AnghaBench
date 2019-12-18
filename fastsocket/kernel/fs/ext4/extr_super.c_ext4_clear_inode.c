#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  jinode; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_journal; } ;

/* Variables and functions */
 TYPE_2__* EXT4_I (struct inode*) ; 
 scalar_t__ EXT4_JOURNAL (struct inode*) ; 
 TYPE_1__* EXT4_SB (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ext4_discard_preallocations (struct inode*) ; 
 int /*<<< orphan*/  jbd2_journal_release_jbd_inode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ext4_clear_inode(struct inode *inode)
{
	ext4_discard_preallocations(inode);
	if (EXT4_JOURNAL(inode))
		jbd2_journal_release_jbd_inode(EXT4_SB(inode->i_sb)->s_journal,
				       &EXT4_I(inode)->jinode);
}