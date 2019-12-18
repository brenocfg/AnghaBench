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

/* Variables and functions */

__attribute__((used)) static void
dtrace_aggregate_count(uint64_t *oval, uint64_t nval, uint64_t arg)
{
#pragma unused(nval, arg) /* __APPLE__ */
	*oval = *oval + 1;
}