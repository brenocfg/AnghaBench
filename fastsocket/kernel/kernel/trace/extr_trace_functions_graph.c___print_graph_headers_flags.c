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
 int TRACE_GRAPH_PRINT_DURATION ; 
 int TRACE_GRAPH_PRINT_PROC ; 
 int TRACE_ITER_LATENCY_FMT ; 
 int /*<<< orphan*/  print_lat_header (struct seq_file*,int) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*) ; 
 int trace_flags ; 

__attribute__((used)) static void __print_graph_headers_flags(struct seq_file *s, u32 flags)
{
	int lat = trace_flags & TRACE_ITER_LATENCY_FMT;

	if (lat)
		print_lat_header(s, flags);

	/* 1st line */
	seq_printf(s, "#");
	if (flags & TRACE_GRAPH_PRINT_ABS_TIME)
		seq_printf(s, "     TIME       ");
	if (flags & TRACE_GRAPH_PRINT_CPU)
		seq_printf(s, " CPU");
	if (flags & TRACE_GRAPH_PRINT_PROC)
		seq_printf(s, "  TASK/PID       ");
	if (lat)
		seq_printf(s, "|||||");
	if (flags & TRACE_GRAPH_PRINT_DURATION)
		seq_printf(s, "  DURATION   ");
	seq_printf(s, "               FUNCTION CALLS\n");

	/* 2nd line */
	seq_printf(s, "#");
	if (flags & TRACE_GRAPH_PRINT_ABS_TIME)
		seq_printf(s, "      |         ");
	if (flags & TRACE_GRAPH_PRINT_CPU)
		seq_printf(s, " |  ");
	if (flags & TRACE_GRAPH_PRINT_PROC)
		seq_printf(s, "   |    |        ");
	if (lat)
		seq_printf(s, "|||||");
	if (flags & TRACE_GRAPH_PRINT_DURATION)
		seq_printf(s, "   |   |      ");
	seq_printf(s, "               |   |   |   |\n");
}