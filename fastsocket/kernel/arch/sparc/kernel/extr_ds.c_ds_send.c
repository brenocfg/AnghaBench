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
struct ldc_channel {int dummy; } ;

/* Variables and functions */
 int __ds_send (struct ldc_channel*,void*,int) ; 
 int /*<<< orphan*/  ds_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ds_send(struct ldc_channel *lp, void *data, int len)
{
	unsigned long flags;
	int err;

	spin_lock_irqsave(&ds_lock, flags);
	err = __ds_send(lp, data, len);
	spin_unlock_irqrestore(&ds_lock, flags);

	return err;
}