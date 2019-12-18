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
struct cpu_signature {int dummy; } ;
struct cpu_info_ctx {int err; struct cpu_signature* cpu_sig; } ;

/* Variables and functions */
 int /*<<< orphan*/  collect_cpu_info_local ; 
 int smp_call_function_single (int,int /*<<< orphan*/ ,struct cpu_info_ctx*,int) ; 

__attribute__((used)) static int collect_cpu_info_on_target(int cpu, struct cpu_signature *cpu_sig)
{
	struct cpu_info_ctx ctx = { .cpu_sig = cpu_sig, .err = 0 };
	int ret;

	ret = smp_call_function_single(cpu, collect_cpu_info_local, &ctx, 1);
	if (!ret)
		ret = ctx.err;

	return ret;
}