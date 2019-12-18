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
struct snd_timer_instance {struct snd_timer_instance* owner; struct snd_timer* timer; int /*<<< orphan*/  slave_active_head; int /*<<< orphan*/  slave_list_head; int /*<<< orphan*/  ack_list; int /*<<< orphan*/  active_list; int /*<<< orphan*/  open_list; } ;
struct snd_timer {int /*<<< orphan*/  module; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct snd_timer_instance*) ; 
 struct snd_timer_instance* kstrdup (char*,int /*<<< orphan*/ ) ; 
 struct snd_timer_instance* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct snd_timer_instance *snd_timer_instance_new(char *owner,
							 struct snd_timer *timer)
{
	struct snd_timer_instance *timeri;
	timeri = kzalloc(sizeof(*timeri), GFP_KERNEL);
	if (timeri == NULL)
		return NULL;
	timeri->owner = kstrdup(owner, GFP_KERNEL);
	if (! timeri->owner) {
		kfree(timeri);
		return NULL;
	}
	INIT_LIST_HEAD(&timeri->open_list);
	INIT_LIST_HEAD(&timeri->active_list);
	INIT_LIST_HEAD(&timeri->ack_list);
	INIT_LIST_HEAD(&timeri->slave_list_head);
	INIT_LIST_HEAD(&timeri->slave_active_head);

	timeri->timer = timer;
	if (timer && !try_module_get(timer->module)) {
		kfree(timeri->owner);
		kfree(timeri);
		return NULL;
	}

	return timeri;
}