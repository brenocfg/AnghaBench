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
typedef  int /*<<< orphan*/  u64 ;
struct trace {scalar_t__ multiple_threads; } ;
struct thread {int pid; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ fprintf (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ fprintf_duration (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 size_t trace__fprintf_tstamp (struct trace*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static size_t trace__fprintf_entry_head(struct trace *trace, struct thread *thread,
					u64 duration, u64 tstamp, FILE *fp)
{
	size_t printed = trace__fprintf_tstamp(trace, tstamp, fp);
	printed += fprintf_duration(duration, fp);

	if (trace->multiple_threads)
		printed += fprintf(fp, "%d ", thread->pid);

	return printed;
}