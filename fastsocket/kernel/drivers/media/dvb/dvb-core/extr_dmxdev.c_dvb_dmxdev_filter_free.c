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
struct TYPE_2__ {int /*<<< orphan*/  queue; int /*<<< orphan*/ * data; } ;
struct dmxdev_filter {int /*<<< orphan*/  mutex; TYPE_1__ buffer; } ;
struct dmxdev {int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMXDEV_STATE_FREE ; 
 int /*<<< orphan*/  dvb_dmxdev_filter_reset (struct dmxdev_filter*) ; 
 int /*<<< orphan*/  dvb_dmxdev_filter_state_set (struct dmxdev_filter*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dvb_dmxdev_filter_stop (struct dmxdev_filter*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vfree (void*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dvb_dmxdev_filter_free(struct dmxdev *dmxdev,
				  struct dmxdev_filter *dmxdevfilter)
{
	mutex_lock(&dmxdev->mutex);
	mutex_lock(&dmxdevfilter->mutex);

	dvb_dmxdev_filter_stop(dmxdevfilter);
	dvb_dmxdev_filter_reset(dmxdevfilter);

	if (dmxdevfilter->buffer.data) {
		void *mem = dmxdevfilter->buffer.data;

		spin_lock_irq(&dmxdev->lock);
		dmxdevfilter->buffer.data = NULL;
		spin_unlock_irq(&dmxdev->lock);
		vfree(mem);
	}

	dvb_dmxdev_filter_state_set(dmxdevfilter, DMXDEV_STATE_FREE);
	wake_up(&dmxdevfilter->buffer.queue);
	mutex_unlock(&dmxdevfilter->mutex);
	mutex_unlock(&dmxdev->mutex);
	return 0;
}