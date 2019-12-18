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
struct probe_trace_point {int /*<<< orphan*/  retprobe; int /*<<< orphan*/  offset; int /*<<< orphan*/  symbol; } ;
struct perf_probe_point {int /*<<< orphan*/  retprobe; int /*<<< orphan*/  offset; int /*<<< orphan*/ * function; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/ * strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int convert_to_perf_probe_point(struct probe_trace_point *tp,
					struct perf_probe_point *pp)
{
	pp->function = strdup(tp->symbol);

	if (pp->function == NULL)
		return -ENOMEM;

	pp->offset = tp->offset;
	pp->retprobe = tp->retprobe;

	return 0;
}