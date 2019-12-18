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
struct TYPE_2__ {unsigned long s_gdb_count; } ;

/* Variables and functions */
 TYPE_1__* EXT2_SB (struct super_block*) ; 
 scalar_t__ ext2_bg_has_super (struct super_block*,int) ; 

unsigned long ext2_bg_num_gdb(struct super_block *sb, int group)
{
	return ext2_bg_has_super(sb, group) ? EXT2_SB(sb)->s_gdb_count : 0;
}