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

/* Variables and functions */
 int TIME_THRESH ; 
 int determine_display_tasks (int) ; 
 int /*<<< orphan*/  draw_c_p_states () ; 
 int /*<<< orphan*/  draw_cpu_usage () ; 
 int /*<<< orphan*/  draw_process_bars () ; 
 int /*<<< orphan*/  draw_wakeups () ; 
 int /*<<< orphan*/  first_time ; 
 int /*<<< orphan*/  last_time ; 
 int /*<<< orphan*/  max_freq ; 
 scalar_t__ numcpus ; 
 int /*<<< orphan*/  open_svg (char const*,scalar_t__,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_close () ; 
 int /*<<< orphan*/  svg_cpu_box (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  svg_legenda () ; 
 int /*<<< orphan*/  svg_time_grid () ; 
 int /*<<< orphan*/  turbo_frequency ; 

__attribute__((used)) static void write_svg_file(const char *filename)
{
	u64 i;
	int count;

	numcpus++;


	count = determine_display_tasks(TIME_THRESH);

	/* We'd like to show at least 15 tasks; be less picky if we have fewer */
	if (count < 15)
		count = determine_display_tasks(TIME_THRESH / 10);

	open_svg(filename, numcpus, count, first_time, last_time);

	svg_time_grid();
	svg_legenda();

	for (i = 0; i < numcpus; i++)
		svg_cpu_box(i, max_freq, turbo_frequency);

	draw_cpu_usage();
	draw_process_bars();
	draw_c_p_states();
	draw_wakeups();

	svg_close();
}