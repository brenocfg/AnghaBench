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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_event_read_unlock () ; 
 int /*<<< orphan*/  trace_record_cmdline_disabled ; 

__attribute__((used)) static void s_stop(struct seq_file *m, void *p)
{
	atomic_dec(&trace_record_cmdline_disabled);
	trace_event_read_unlock();
}