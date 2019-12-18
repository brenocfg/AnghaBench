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
typedef  scalar_t__ int64_t ;

/* Variables and functions */

__attribute__((used)) static void
dt_aggregate_llquantize(int64_t *existing, int64_t *new, size_t size)
{
	int i;

	for (i = 1; i < size / sizeof (int64_t); i++)
		existing[i] = existing[i] + new[i];
}