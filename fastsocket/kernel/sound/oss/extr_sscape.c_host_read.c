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
struct sscape_info {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  HOST_CTRL ; 
 int /*<<< orphan*/  HOST_DATA ; 
 int /*<<< orphan*/  PORT (int /*<<< orphan*/ ) ; 
 int RX_READY ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int host_read(struct sscape_info *devc)
{
	unsigned long flags;
	int timeout_val;
	unsigned char data;

	spin_lock_irqsave(&devc->lock,flags);
	/*
	 * Read a byte
	 */

	for (timeout_val = 10000; timeout_val > 0; timeout_val--)
		if (inb(PORT(HOST_CTRL)) & RX_READY)
			break;

	if (timeout_val <= 0)
	{
		spin_unlock_irqrestore(&devc->lock,flags);
		return -1;
	}
	data = inb(PORT(HOST_DATA));
	spin_unlock_irqrestore(&devc->lock,flags);
	return data;
}