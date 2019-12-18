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
struct garmin_data {int /*<<< orphan*/  lock; scalar_t__ outsize; scalar_t__ insize; } ;

/* Variables and functions */
 int /*<<< orphan*/  pkt_clear (struct garmin_data*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int garmin_clear(struct garmin_data *garmin_data_p)
{
	unsigned long flags;
	int status = 0;

	/* flush all queued data */
	pkt_clear(garmin_data_p);

	spin_lock_irqsave(&garmin_data_p->lock, flags);
	garmin_data_p->insize = 0;
	garmin_data_p->outsize = 0;
	spin_unlock_irqrestore(&garmin_data_p->lock, flags);

	return status;
}