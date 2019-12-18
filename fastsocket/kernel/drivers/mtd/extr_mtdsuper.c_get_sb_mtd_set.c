#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct super_block {int /*<<< orphan*/  s_dev; struct mtd_info* s_mtd; } ;
struct mtd_info {int /*<<< orphan*/  index; } ;

/* Variables and functions */
 int /*<<< orphan*/  MKDEV (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MTD_BLOCK_MAJOR ; 

__attribute__((used)) static int get_sb_mtd_set(struct super_block *sb, void *_mtd)
{
	struct mtd_info *mtd = _mtd;

	sb->s_mtd = mtd;
	sb->s_dev = MKDEV(MTD_BLOCK_MAJOR, mtd->index);
	return 0;
}