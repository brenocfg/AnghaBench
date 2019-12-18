#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct mx3fb_info {int /*<<< orphan*/  cookie; TYPE_1__* txd; struct mx3fb_data* mx3fb; } ;
struct mx3fb_data {int /*<<< orphan*/  lock; } ;
struct TYPE_6__ {TYPE_2__* device; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* device_terminate_all ) (TYPE_3__*) ;} ;
struct TYPE_4__ {TYPE_3__* chan; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  sdc_fb_uninit (struct mx3fb_info*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void sdc_disable_channel(struct mx3fb_info *mx3_fbi)
{
	struct mx3fb_data *mx3fb = mx3_fbi->mx3fb;
	uint32_t enabled;
	unsigned long flags;

	spin_lock_irqsave(&mx3fb->lock, flags);

	enabled = sdc_fb_uninit(mx3_fbi);

	spin_unlock_irqrestore(&mx3fb->lock, flags);

	mx3_fbi->txd->chan->device->device_terminate_all(mx3_fbi->txd->chan);
	mx3_fbi->txd = NULL;
	mx3_fbi->cookie = -EINVAL;
}