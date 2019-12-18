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
struct ct_timer_instance {int /*<<< orphan*/  instance_list; int /*<<< orphan*/  substream; struct ct_atc_pcm* apcm; struct ct_timer* timer_base; int /*<<< orphan*/  running_list; int /*<<< orphan*/  lock; } ;
struct ct_timer {int /*<<< orphan*/  list_lock; int /*<<< orphan*/  instance_head; TYPE_1__* ops; } ;
struct ct_atc_pcm {int /*<<< orphan*/  substream; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* init ) (struct ct_timer_instance*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct ct_timer_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct ct_timer_instance*) ; 

struct ct_timer_instance *
ct_timer_instance_new(struct ct_timer *atimer, struct ct_atc_pcm *apcm)
{
	struct ct_timer_instance *ti;

	ti = kzalloc(sizeof(*ti), GFP_KERNEL);
	if (!ti)
		return NULL;
	spin_lock_init(&ti->lock);
	INIT_LIST_HEAD(&ti->instance_list);
	INIT_LIST_HEAD(&ti->running_list);
	ti->timer_base = atimer;
	ti->apcm = apcm;
	ti->substream = apcm->substream;
	if (atimer->ops->init)
		atimer->ops->init(ti);

	spin_lock_irq(&atimer->list_lock);
	list_add(&ti->instance_list, &atimer->instance_head);
	spin_unlock_irq(&atimer->list_lock);

	return ti;
}