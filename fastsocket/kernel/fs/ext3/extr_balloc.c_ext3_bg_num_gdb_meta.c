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
struct super_block {int dummy; } ;

/* Variables and functions */
 unsigned long EXT3_DESC_PER_BLOCK (struct super_block*) ; 

__attribute__((used)) static unsigned long ext3_bg_num_gdb_meta(struct super_block *sb, int group)
{
	unsigned long metagroup = group / EXT3_DESC_PER_BLOCK(sb);
	unsigned long first = metagroup * EXT3_DESC_PER_BLOCK(sb);
	unsigned long last = first + EXT3_DESC_PER_BLOCK(sb) - 1;

	if (group == first || group == first + 1 || group == last)
		return 1;
	return 0;
}