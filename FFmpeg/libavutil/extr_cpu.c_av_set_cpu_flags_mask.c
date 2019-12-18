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

/* Variables and functions */
 int /*<<< orphan*/  atomic_store_explicit (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_flags ; 
 int get_cpu_flags () ; 
 int /*<<< orphan*/  memory_order_relaxed ; 

void av_set_cpu_flags_mask(int mask)
{
    atomic_store_explicit(&cpu_flags, get_cpu_flags() & mask,
                          memory_order_relaxed);
}