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
struct ext4_sb_info {unsigned long s_stripe; unsigned long s_blocks_per_group; TYPE_1__* s_es; } ;
struct TYPE_2__ {int /*<<< orphan*/  s_raid_stripe_width; int /*<<< orphan*/  s_raid_stride; } ;

/* Variables and functions */
 unsigned long le16_to_cpu (int /*<<< orphan*/ ) ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long ext4_get_stripe_size(struct ext4_sb_info *sbi)
{
	unsigned long stride = le16_to_cpu(sbi->s_es->s_raid_stride);
	unsigned long stripe_width =
			le32_to_cpu(sbi->s_es->s_raid_stripe_width);

	if (sbi->s_stripe && sbi->s_stripe <= sbi->s_blocks_per_group)
		return sbi->s_stripe;

	if (stripe_width <= sbi->s_blocks_per_group)
		return stripe_width;

	if (stride <= sbi->s_blocks_per_group)
		return stride;

	return 0;
}