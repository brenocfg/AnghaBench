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
typedef  scalar_t__ uint8_t ;
struct TYPE_3__ {int /*<<< orphan*/  groups_count; scalar_t__* groups; } ;
typedef  TYPE_1__ m68k_info ;
typedef  scalar_t__ m68k_group_type ;

/* Variables and functions */

__attribute__((used)) static void set_insn_group(m68k_info *info, m68k_group_type group)
{
	info->groups[info->groups_count++] = (uint8_t)group;
}