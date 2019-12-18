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
struct udf_bitmap {int /*<<< orphan*/ * s_block_bitmap; } ;
struct super_block {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int __load_block_bitmap (struct super_block*,struct udf_bitmap*,unsigned int) ; 

__attribute__((used)) static inline int load_block_bitmap(struct super_block *sb,
				    struct udf_bitmap *bitmap,
				    unsigned int block_group)
{
	int slot;

	slot = __load_block_bitmap(sb, bitmap, block_group);

	if (slot < 0)
		return slot;

	if (!bitmap->s_block_bitmap[slot])
		return -EIO;

	return slot;
}