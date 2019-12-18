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
struct timespec {int tv_sec; int tv_nsec; } ;
struct slow_work {int /*<<< orphan*/  mark; } ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 struct timespec CURRENT_TIME ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 
 struct timespec timespec_sub (struct timespec,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void slow_work_print_mark(struct seq_file *m, struct slow_work *work)
{
	struct timespec now, diff;

	now = CURRENT_TIME;
	diff = timespec_sub(now, work->mark);

	if (diff.tv_sec < 0)
		seq_puts(m, "  -ve ");
	else if (diff.tv_sec == 0 && diff.tv_nsec < 1000)
		seq_printf(m, "%3luns ", diff.tv_nsec);
	else if (diff.tv_sec == 0 && diff.tv_nsec < 1000000)
		seq_printf(m, "%3luus ", diff.tv_nsec / 1000);
	else if (diff.tv_sec == 0 && diff.tv_nsec < 1000000000)
		seq_printf(m, "%3lums ", diff.tv_nsec / 1000000);
	else if (diff.tv_sec <= 1)
		seq_puts(m, "   1s ");
	else if (diff.tv_sec < 60)
		seq_printf(m, "%4lus ", diff.tv_sec);
	else if (diff.tv_sec < 60 * 60)
		seq_printf(m, "%4lum ", diff.tv_sec / 60);
	else if (diff.tv_sec < 60 * 60 * 24)
		seq_printf(m, "%4luh ", diff.tv_sec / 3600);
	else
		seq_puts(m, "exces ");
}