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
struct urb {int /*<<< orphan*/  status; int /*<<< orphan*/  transfer_buffer_length; int /*<<< orphan*/  actual_length; struct acm_wb* context; } ;
struct acm_wb {struct acm* instance; } ;
struct acm {int /*<<< orphan*/  drain_wait; int /*<<< orphan*/  work; int /*<<< orphan*/  write_lock; TYPE_1__* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ ACM_READY (struct acm*) ; 
 int /*<<< orphan*/  acm_write_done (struct acm*,struct acm_wb*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ verbose ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acm_write_bulk(struct urb *urb)
{
	struct acm_wb *wb = urb->context;
	struct acm *acm = wb->instance;
	unsigned long flags;

	if (verbose || urb->status
			|| (urb->actual_length != urb->transfer_buffer_length))
		dev_dbg(&acm->data->dev, "tx %d/%d bytes -- > %d\n",
			urb->actual_length,
			urb->transfer_buffer_length,
			urb->status);

	spin_lock_irqsave(&acm->write_lock, flags);
	acm_write_done(acm, wb);
	spin_unlock_irqrestore(&acm->write_lock, flags);
	if (ACM_READY(acm))
		schedule_work(&acm->work);
	else
		wake_up_interruptible(&acm->drain_wait);
}