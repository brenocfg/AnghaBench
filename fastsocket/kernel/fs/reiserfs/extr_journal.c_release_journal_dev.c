#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {scalar_t__ s_dev; } ;
struct reiserfs_journal {TYPE_1__* j_dev_bd; int /*<<< orphan*/  j_dev_mode; } ;
struct TYPE_3__ {scalar_t__ bd_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  bd_release (TYPE_1__*) ; 
 int blkdev_put (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reiserfs_warning (struct super_block*,char*,char*,int) ; 

__attribute__((used)) static int release_journal_dev(struct super_block *super,
			       struct reiserfs_journal *journal)
{
	int result;

	result = 0;

	if (journal->j_dev_bd != NULL) {
		if (journal->j_dev_bd->bd_dev != super->s_dev)
			bd_release(journal->j_dev_bd);
		result = blkdev_put(journal->j_dev_bd, journal->j_dev_mode);
		journal->j_dev_bd = NULL;
	}

	if (result != 0) {
		reiserfs_warning(super, "sh-457",
				 "Cannot release journal device: %i", result);
	}
	return result;
}