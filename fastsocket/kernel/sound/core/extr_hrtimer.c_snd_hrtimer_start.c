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
struct snd_timer {int sticks; struct snd_hrtimer* private_data; } ;
struct snd_hrtimer {int /*<<< orphan*/  running; int /*<<< orphan*/  hrt; } ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_to_ktime (int) ; 
 int resolution ; 

__attribute__((used)) static int snd_hrtimer_start(struct snd_timer *t)
{
	struct snd_hrtimer *stime = t->private_data;

	atomic_set(&stime->running, 0);
	hrtimer_cancel(&stime->hrt);
	hrtimer_start(&stime->hrt, ns_to_ktime(t->sticks * resolution),
		      HRTIMER_MODE_REL);
	atomic_set(&stime->running, 1);
	return 0;
}