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
struct perf_read_values {int counters_max; int threads; void** value; void* countername; void* counterrawid; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 void* realloc (void*,int) ; 

__attribute__((used)) static void perf_read_values__enlarge_counters(struct perf_read_values *values)
{
	int i;

	values->counters_max *= 2;
	values->counterrawid = realloc(values->counterrawid,
				       values->counters_max * sizeof(*values->counterrawid));
	values->countername = realloc(values->countername,
				      values->counters_max * sizeof(*values->countername));
	if (!values->counterrawid || !values->countername)
		die("failed to enlarge read_values counters arrays");

	for (i = 0; i < values->threads; i++) {
		values->value[i] = realloc(values->value[i],
					   values->counters_max * sizeof(**values->value));
		if (!values->value[i])
			die("failed to enlarge read_values counters arrays");
	}
}