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
struct symbol {int dummy; } ;
struct probe_trace_point {int /*<<< orphan*/  symbol; } ;
struct perf_probe_point {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 struct symbol* __find_kernel_function_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int convert_to_perf_probe_point (struct probe_trace_point*,struct perf_probe_point*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int kprobe_convert_to_perf_probe(struct probe_trace_point *tp,
					struct perf_probe_point *pp)
{
	struct symbol *sym;

	sym = __find_kernel_function_by_name(tp->symbol, NULL);
	if (!sym) {
		pr_err("Failed to find symbol %s in kernel.\n", tp->symbol);
		return -ENOENT;
	}

	return convert_to_perf_probe_point(tp, pp);
}