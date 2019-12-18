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
struct TYPE_2__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct usbatm_channel {TYPE_1__ delay; int /*<<< orphan*/  tasklet; int /*<<< orphan*/  list; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbatm_tasklet_schedule ; 

__attribute__((used)) static void usbatm_init_channel(struct usbatm_channel *channel)
{
	spin_lock_init(&channel->lock);
	INIT_LIST_HEAD(&channel->list);
	channel->delay.function = usbatm_tasklet_schedule;
	channel->delay.data = (unsigned long) &channel->tasklet;
	init_timer(&channel->delay);
}