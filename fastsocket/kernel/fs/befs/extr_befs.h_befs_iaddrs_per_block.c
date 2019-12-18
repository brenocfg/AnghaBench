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
typedef  int /*<<< orphan*/  befs_disk_inode_addr ;
struct TYPE_2__ {int block_size; } ;

/* Variables and functions */
 TYPE_1__* BEFS_SB (struct super_block*) ; 

__attribute__((used)) static inline unsigned int
befs_iaddrs_per_block(struct super_block *sb)
{
	return BEFS_SB(sb)->block_size / sizeof (befs_disk_inode_addr);
}