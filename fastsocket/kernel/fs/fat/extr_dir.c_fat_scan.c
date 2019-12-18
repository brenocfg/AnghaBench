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
struct super_block {int dummy; } ;
struct inode {struct super_block* i_sb; } ;
struct fat_slot_info {int nr_slots; TYPE_1__* de; int /*<<< orphan*/ * bh; int /*<<< orphan*/  i_pos; scalar_t__ slot_off; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  MSDOS_NAME ; 
 scalar_t__ fat_get_short_entry (struct inode*,scalar_t__*,int /*<<< orphan*/ **,TYPE_1__**) ; 
 int /*<<< orphan*/  fat_make_i_pos (struct super_block*,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,unsigned char const*,int /*<<< orphan*/ ) ; 

int fat_scan(struct inode *dir, const unsigned char *name,
	     struct fat_slot_info *sinfo)
{
	struct super_block *sb = dir->i_sb;

	sinfo->slot_off = 0;
	sinfo->bh = NULL;
	while (fat_get_short_entry(dir, &sinfo->slot_off, &sinfo->bh,
				   &sinfo->de) >= 0) {
		if (!strncmp(sinfo->de->name, name, MSDOS_NAME)) {
			sinfo->slot_off -= sizeof(*sinfo->de);
			sinfo->nr_slots = 1;
			sinfo->i_pos = fat_make_i_pos(sb, sinfo->bh, sinfo->de);
			return 0;
		}
	}
	return -ENOENT;
}