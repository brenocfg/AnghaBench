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
struct perf_read_values {int threads_max; void* value; void* tid; void* pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  die (char*) ; 
 void* realloc (void*,int) ; 

__attribute__((used)) static void perf_read_values__enlarge_threads(struct perf_read_values *values)
{
	values->threads_max *= 2;
	values->pid = realloc(values->pid,
			      values->threads_max * sizeof(*values->pid));
	values->tid = realloc(values->tid,
			      values->threads_max * sizeof(*values->tid));
	values->value = realloc(values->value,
				values->threads_max * sizeof(*values->value));
	if (!values->pid || !values->tid || !values->value)
		die("failed to enlarge read_values threads arrays");
}