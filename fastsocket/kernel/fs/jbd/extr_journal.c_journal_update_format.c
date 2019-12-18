#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* j_superblock; } ;
typedef  TYPE_2__ journal_t ;
struct TYPE_8__ {int /*<<< orphan*/  h_blocktype; } ;
struct TYPE_10__ {TYPE_1__ s_header; } ;
typedef  TYPE_3__ journal_superblock_t ;

/* Variables and functions */
 int EINVAL ; 
#define  JFS_SUPERBLOCK_V1 129 
#define  JFS_SUPERBLOCK_V2 128 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int journal_convert_superblock_v1 (TYPE_2__*,TYPE_3__*) ; 
 int journal_get_superblock (TYPE_2__*) ; 

int journal_update_format (journal_t *journal)
{
	journal_superblock_t *sb;
	int err;

	err = journal_get_superblock(journal);
	if (err)
		return err;

	sb = journal->j_superblock;

	switch (be32_to_cpu(sb->s_header.h_blocktype)) {
	case JFS_SUPERBLOCK_V2:
		return 0;
	case JFS_SUPERBLOCK_V1:
		return journal_convert_superblock_v1(journal, sb);
	default:
		break;
	}
	return -EINVAL;
}