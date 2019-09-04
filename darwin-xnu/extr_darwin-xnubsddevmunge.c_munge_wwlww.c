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
typedef  scalar_t__ uint64_t ;
typedef  scalar_t__ uint32_t ;

/* Variables and functions */

void
munge_wwlww(void *args)
{
	volatile uint64_t *out_args = (volatile uint64_t*)args;
	volatile uint32_t *in_args = (volatile uint32_t*)args;

	out_args[4] = in_args[5];
	out_args[3] = in_args[4];
	out_args[2] = *(volatile uint64_t*)&in_args[2];
	out_args[1] = in_args[1];
	out_args[0] = in_args[0];
}