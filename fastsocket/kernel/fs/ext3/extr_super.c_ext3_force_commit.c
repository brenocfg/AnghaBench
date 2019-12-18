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
struct super_block {int s_flags; } ;
typedef  int /*<<< orphan*/  journal_t ;
struct TYPE_2__ {int /*<<< orphan*/ * s_journal; } ;

/* Variables and functions */
 TYPE_1__* EXT3_SB (struct super_block*) ; 
 int MS_RDONLY ; 
 int ext3_journal_force_commit (int /*<<< orphan*/ *) ; 

int ext3_force_commit(struct super_block *sb)
{
	journal_t *journal;
	int ret;

	if (sb->s_flags & MS_RDONLY)
		return 0;

	journal = EXT3_SB(sb)->s_journal;
	ret = ext3_journal_force_commit(journal);
	return ret;
}