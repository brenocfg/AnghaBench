#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct super_block {TYPE_2__* s_bdev; } ;
struct ext4_sb_info {scalar_t__ s_kbytes_written; TYPE_1__* s_buddy_cache; } ;
struct ext4_attr {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_6__ {int s_sectors_written_start; } ;
struct TYPE_5__ {int /*<<< orphan*/  bd_part; } ;
struct TYPE_4__ {struct super_block* i_sb; } ;

/* Variables and functions */
 TYPE_3__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int part_stat_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sectors ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static ssize_t lifetime_write_kbytes_show(struct ext4_attr *a,
					  struct ext4_sb_info *sbi, char *buf)
{
	struct super_block *sb = sbi->s_buddy_cache->i_sb;

	return snprintf(buf, PAGE_SIZE, "%llu\n",
			sbi->s_kbytes_written + 
			((part_stat_read(sb->s_bdev->bd_part, sectors[1]) -
			  EXT4_SB(sb)->s_sectors_written_start) >> 1));
}