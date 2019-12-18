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
struct TYPE_2__ {int bit; int /*<<< orphan*/  btype; int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int DEF_BIND_COUNT ; 
 size_t IN_BIND_OFFS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* in_vk_def_binds ; 

__attribute__((used)) static void in_vk_get_def_binds(int *binds)
{
	int i;

	for (i = 0; i < DEF_BIND_COUNT; i++)
		binds[IN_BIND_OFFS(in_vk_def_binds[i].code, in_vk_def_binds[i].btype)] =
			1 << in_vk_def_binds[i].bit;
}