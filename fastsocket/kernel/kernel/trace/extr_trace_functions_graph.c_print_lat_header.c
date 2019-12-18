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
typedef  int u32 ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int TRACE_GRAPH_PRINT_ABS_TIME ; 
 int TRACE_GRAPH_PRINT_CPU ; 
 int TRACE_GRAPH_PRINT_PROC ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,char const*) ; 

__attribute__((used)) static void print_lat_header(struct seq_file *s, u32 flags)
{
	static const char spaces[] = "                "	/* 16 spaces */
		"    "					/* 4 spaces */
		"                 ";			/* 17 spaces */
	int size = 0;

	if (flags & TRACE_GRAPH_PRINT_ABS_TIME)
		size += 16;
	if (flags & TRACE_GRAPH_PRINT_CPU)
		size += 4;
	if (flags & TRACE_GRAPH_PRINT_PROC)
		size += 17;

	seq_printf(s, "#%.*s  _-----=> irqs-off        \n", size, spaces);
	seq_printf(s, "#%.*s / _----=> need-resched    \n", size, spaces);
	seq_printf(s, "#%.*s| / _---=> hardirq/softirq \n", size, spaces);
	seq_printf(s, "#%.*s|| / _--=> preempt-depth   \n", size, spaces);
	seq_printf(s, "#%.*s||| / _-=> lock-depth      \n", size, spaces);
	seq_printf(s, "#%.*s|||| /                     \n", size, spaces);
}