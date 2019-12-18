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
struct snd_timer {struct snd_hrtimer* private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/  function; } ;
struct snd_hrtimer {int /*<<< orphan*/  running; TYPE_1__ hrt; struct snd_timer* timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  HRTIMER_MODE_REL ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_hrtimer* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_hrtimer_callback ; 

__attribute__((used)) static int snd_hrtimer_open(struct snd_timer *t)
{
	struct snd_hrtimer *stime;

	stime = kmalloc(sizeof(*stime), GFP_KERNEL);
	if (!stime)
		return -ENOMEM;
	hrtimer_init(&stime->hrt, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	stime->timer = t;
	stime->hrt.function = snd_hrtimer_callback;
	atomic_set(&stime->running, 0);
	t->private_data = stime;
	return 0;
}