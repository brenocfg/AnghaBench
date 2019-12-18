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
typedef  scalar_t__ u64 ;
struct trace_seq {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  NSEC_PER_SEC ; 
 unsigned long do_div (scalar_t__,int /*<<< orphan*/ ) ; 
 int trace_seq_printf (struct trace_seq*,char*,unsigned long,unsigned long) ; 

__attribute__((used)) static int print_graph_abs_time(u64 t, struct trace_seq *s)
{
	unsigned long usecs_rem;

	usecs_rem = do_div(t, NSEC_PER_SEC);
	usecs_rem /= 1000;

	return trace_seq_printf(s, "%5lu.%06lu |  ",
			(unsigned long)t, usecs_rem);
}