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
struct flush_icache_range_args {unsigned long start; unsigned long end; } ;

/* Variables and functions */
 int /*<<< orphan*/  instruction_hazard () ; 
 int /*<<< orphan*/  local_r4k_flush_icache_range_ipi ; 
 int /*<<< orphan*/  r4k_on_each_cpu (int /*<<< orphan*/ ,struct flush_icache_range_args*,int) ; 

__attribute__((used)) static void r4k_flush_icache_range(unsigned long start, unsigned long end)
{
	struct flush_icache_range_args args;

	args.start = start;
	args.end = end;

	r4k_on_each_cpu(local_r4k_flush_icache_range_ipi, &args, 1);
	instruction_hazard();
}