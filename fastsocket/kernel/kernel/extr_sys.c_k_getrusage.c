#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct task_struct {TYPE_1__* signal; } ;
struct rusage {unsigned long ru_maxrss; int /*<<< orphan*/  ru_stime; int /*<<< orphan*/  ru_utime; int /*<<< orphan*/  ru_oublock; int /*<<< orphan*/  ru_inblock; int /*<<< orphan*/  ru_majflt; int /*<<< orphan*/  ru_minflt; int /*<<< orphan*/  ru_nivcsw; int /*<<< orphan*/  ru_nvcsw; } ;
struct mm_struct {int dummy; } ;
typedef  int /*<<< orphan*/  cputime_t ;
struct TYPE_2__ {unsigned long maxrss; unsigned long cmaxrss; int /*<<< orphan*/  oublock; int /*<<< orphan*/  inblock; int /*<<< orphan*/  maj_flt; int /*<<< orphan*/  min_flt; int /*<<< orphan*/  nivcsw; int /*<<< orphan*/  nvcsw; int /*<<< orphan*/  coublock; int /*<<< orphan*/  cinblock; int /*<<< orphan*/  cmaj_flt; int /*<<< orphan*/  cmin_flt; int /*<<< orphan*/  cnivcsw; int /*<<< orphan*/  cnvcsw; int /*<<< orphan*/  cstime; int /*<<< orphan*/  cutime; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int PAGE_SIZE ; 
#define  RUSAGE_BOTH 130 
#define  RUSAGE_CHILDREN 129 
#define  RUSAGE_SELF 128 
 int RUSAGE_THREAD ; 
 int /*<<< orphan*/  accumulate_thread_rusage (struct task_struct*,struct rusage*) ; 
 int /*<<< orphan*/  cputime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cputime_to_timeval (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cputime_zero ; 
 int /*<<< orphan*/  current ; 
 struct mm_struct* get_task_mm (struct task_struct*) ; 
 int /*<<< orphan*/  lock_task_sighand (struct task_struct*,unsigned long*) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mmput (struct mm_struct*) ; 
 struct task_struct* next_thread (struct task_struct*) ; 
 int /*<<< orphan*/  setmax_mm_hiwater_rss (unsigned long*,struct mm_struct*) ; 
 int /*<<< orphan*/  task_times (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_group_times (struct task_struct*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_task_sighand (struct task_struct*,unsigned long*) ; 

__attribute__((used)) static void k_getrusage(struct task_struct *p, int who, struct rusage *r)
{
	struct task_struct *t;
	unsigned long flags;
	cputime_t tgutime, tgstime, utime, stime;
	unsigned long maxrss = 0;

	memset((char *) r, 0, sizeof *r);
	utime = stime = cputime_zero;

	if (who == RUSAGE_THREAD) {
		task_times(current, &utime, &stime);
		accumulate_thread_rusage(p, r);
		maxrss = p->signal->maxrss;
		goto out;
	}

	if (!lock_task_sighand(p, &flags))
		return;

	switch (who) {
		case RUSAGE_BOTH:
		case RUSAGE_CHILDREN:
			utime = p->signal->cutime;
			stime = p->signal->cstime;
			r->ru_nvcsw = p->signal->cnvcsw;
			r->ru_nivcsw = p->signal->cnivcsw;
			r->ru_minflt = p->signal->cmin_flt;
			r->ru_majflt = p->signal->cmaj_flt;
			r->ru_inblock = p->signal->cinblock;
			r->ru_oublock = p->signal->coublock;
			maxrss = p->signal->cmaxrss;

			if (who == RUSAGE_CHILDREN)
				break;

		case RUSAGE_SELF:
			thread_group_times(p, &tgutime, &tgstime);
			utime = cputime_add(utime, tgutime);
			stime = cputime_add(stime, tgstime);
			r->ru_nvcsw += p->signal->nvcsw;
			r->ru_nivcsw += p->signal->nivcsw;
			r->ru_minflt += p->signal->min_flt;
			r->ru_majflt += p->signal->maj_flt;
			r->ru_inblock += p->signal->inblock;
			r->ru_oublock += p->signal->oublock;
			if (maxrss < p->signal->maxrss)
				maxrss = p->signal->maxrss;
			t = p;
			do {
				accumulate_thread_rusage(t, r);
				t = next_thread(t);
			} while (t != p);
			break;

		default:
			BUG();
	}
	unlock_task_sighand(p, &flags);

out:
	cputime_to_timeval(utime, &r->ru_utime);
	cputime_to_timeval(stime, &r->ru_stime);

	if (who != RUSAGE_CHILDREN) {
		struct mm_struct *mm = get_task_mm(p);
		if (mm) {
			setmax_mm_hiwater_rss(&maxrss, mm);
			mmput(mm);
		}
	}
	r->ru_maxrss = maxrss * (PAGE_SIZE / 1024); /* convert pages to KBs */
}