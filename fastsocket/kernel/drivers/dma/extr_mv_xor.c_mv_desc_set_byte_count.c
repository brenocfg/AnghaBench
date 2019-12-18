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
typedef  int /*<<< orphan*/  u32 ;
struct mv_xor_desc_slot {struct mv_xor_desc* hw_desc; } ;
struct mv_xor_desc {int /*<<< orphan*/  byte_count; } ;

/* Variables and functions */

__attribute__((used)) static void mv_desc_set_byte_count(struct mv_xor_desc_slot *desc,
				   u32 byte_count)
{
	struct mv_xor_desc *hw_desc = desc->hw_desc;
	hw_desc->byte_count = byte_count;
}