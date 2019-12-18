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
struct super_block {int dummy; } ;
struct fatent_operations {int (* ent_bread ) (struct super_block*,struct fat_entry*,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* ent_blocknr ) (struct super_block*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ;} ;
struct fat_entry {int /*<<< orphan*/  entry; } ;
typedef  int /*<<< orphan*/  sector_t ;
struct TYPE_2__ {struct fatent_operations* fatent_ops; } ;

/* Variables and functions */
 TYPE_1__* MSDOS_SB (struct super_block*) ; 
 int /*<<< orphan*/  fatent_brelse (struct fat_entry*) ; 
 int /*<<< orphan*/  stub1 (struct super_block*,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int stub2 (struct super_block*,struct fat_entry*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int fat_ent_read_block(struct super_block *sb,
				     struct fat_entry *fatent)
{
	struct fatent_operations *ops = MSDOS_SB(sb)->fatent_ops;
	sector_t blocknr;
	int offset;

	fatent_brelse(fatent);
	ops->ent_blocknr(sb, fatent->entry, &offset, &blocknr);
	return ops->ent_bread(sb, fatent, offset, blocknr);
}