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
struct seq_file {int dummy; } ;
struct hrtimer {int /*<<< orphan*/  start_pid; int /*<<< orphan*/  start_comm; struct hrtimer* start_site; int /*<<< orphan*/  state; struct hrtimer* function; } ;

/* Variables and functions */
 int /*<<< orphan*/  SEQ_printf (struct seq_file*,char*,...) ; 
 int TASK_COMM_LEN ; 
 int /*<<< orphan*/  hrtimer_get_expires (struct hrtimer*) ; 
 int /*<<< orphan*/  hrtimer_get_softexpires (struct hrtimer*) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  print_name_offset (struct seq_file*,struct hrtimer*) ; 

__attribute__((used)) static void
print_timer(struct seq_file *m, struct hrtimer *taddr, struct hrtimer *timer,
	    int idx, u64 now)
{
#ifdef CONFIG_TIMER_STATS
	char tmp[TASK_COMM_LEN + 1];
#endif
	SEQ_printf(m, " #%d: ", idx);
	print_name_offset(m, taddr);
	SEQ_printf(m, ", ");
	print_name_offset(m, timer->function);
	SEQ_printf(m, ", S:%02lx", timer->state);
#ifdef CONFIG_TIMER_STATS
	SEQ_printf(m, ", ");
	print_name_offset(m, timer->start_site);
	memcpy(tmp, timer->start_comm, TASK_COMM_LEN);
	tmp[TASK_COMM_LEN] = 0;
	SEQ_printf(m, ", %s/%d", tmp, timer->start_pid);
#endif
	SEQ_printf(m, "\n");
	SEQ_printf(m, " # expires at %Lu-%Lu nsecs [in %Ld to %Ld nsecs]\n",
		(unsigned long long)ktime_to_ns(hrtimer_get_softexpires(timer)),
		(unsigned long long)ktime_to_ns(hrtimer_get_expires(timer)),
		(long long)(ktime_to_ns(hrtimer_get_softexpires(timer)) - now),
		(long long)(ktime_to_ns(hrtimer_get_expires(timer)) - now));
}