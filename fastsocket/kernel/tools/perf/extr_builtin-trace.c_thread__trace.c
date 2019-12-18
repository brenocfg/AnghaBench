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
struct thread_trace {int /*<<< orphan*/  nr_events; } ;
struct thread {struct thread_trace* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  PERF_COLOR_RED ; 
 int /*<<< orphan*/  color_fprintf (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stdout ; 
 struct thread_trace* thread_trace__new () ; 

__attribute__((used)) static struct thread_trace *thread__trace(struct thread *thread)
{
	struct thread_trace *ttrace;

	if (thread == NULL)
		goto fail;

	if (thread->priv == NULL)
		thread->priv = thread_trace__new();
		
	if (thread->priv == NULL)
		goto fail;

	ttrace = thread->priv;
	++ttrace->nr_events;

	return ttrace;
fail:
	color_fprintf(stdout, PERF_COLOR_RED,
		      "WARNING: not enough memory, dropping samples!\n");
	return NULL;
}