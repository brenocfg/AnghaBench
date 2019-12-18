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
struct mv_xor_desc_slot {struct mv_xor_desc* hw_desc; } ;
struct mv_xor_desc {int status; int desc_command; scalar_t__ phy_next_desc; } ;

/* Variables and functions */

__attribute__((used)) static void mv_desc_init(struct mv_xor_desc_slot *desc, unsigned long flags)
{
	struct mv_xor_desc *hw_desc = desc->hw_desc;

	hw_desc->status = (1 << 31);
	hw_desc->phy_next_desc = 0;
	hw_desc->desc_command = (1 << 31);
}