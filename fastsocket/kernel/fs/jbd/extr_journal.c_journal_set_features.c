#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* j_superblock; } ;
typedef  TYPE_1__ journal_t ;
struct TYPE_7__ {int /*<<< orphan*/  s_feature_incompat; int /*<<< orphan*/  s_feature_ro_compat; int /*<<< orphan*/  s_feature_compat; } ;
typedef  TYPE_2__ journal_superblock_t ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_be32 (unsigned long) ; 
 int /*<<< orphan*/  jbd_debug (int,char*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  journal_check_available_features (TYPE_1__*,unsigned long,unsigned long,unsigned long) ; 
 scalar_t__ journal_check_used_features (TYPE_1__*,unsigned long,unsigned long,unsigned long) ; 

int journal_set_features (journal_t *journal, unsigned long compat,
			  unsigned long ro, unsigned long incompat)
{
	journal_superblock_t *sb;

	if (journal_check_used_features(journal, compat, ro, incompat))
		return 1;

	if (!journal_check_available_features(journal, compat, ro, incompat))
		return 0;

	jbd_debug(1, "Setting new features 0x%lx/0x%lx/0x%lx\n",
		  compat, ro, incompat);

	sb = journal->j_superblock;

	sb->s_feature_compat    |= cpu_to_be32(compat);
	sb->s_feature_ro_compat |= cpu_to_be32(ro);
	sb->s_feature_incompat  |= cpu_to_be32(incompat);

	return 1;
}