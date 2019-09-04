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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */

void 
munge_lw(void *args)
{
	volatile uint64_t *out_args = (volatile uint64_t*)args;
	volatile uint32_t *in_args = (volatile uint32_t*)args;

	out_args[1] = in_args[2];
	out_args[0] = *(volatile uint64_t*)&in_args[0];
}