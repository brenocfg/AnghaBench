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
 int /*<<< orphan*/  _flush_cache_copyback_all () ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  flushcache_cpumask ; 
 int /*<<< orphan*/  smp_processor_id () ; 

void smp_flush_cache_all_interrupt(void)
{
	_flush_cache_copyback_all();
	clear_bit(smp_processor_id(), &flushcache_cpumask);
}