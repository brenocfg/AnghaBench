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
 int TX_READY ; 
 int inb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  outb (unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int host_write(struct sscape_info *devc, unsigned char *data, int count)
{
	unsigned long flags;
	int i, timeout_val;

	spin_lock_irqsave(&devc->lock,flags);
	/*
	 * Send the command and data bytes
	 */

	for (i = 0; i < count; i++)
	{
		for (timeout_val = 10000; timeout_val > 0; timeout_val--)
			if (inb(PORT(HOST_CTRL)) & TX_READY)
				break;

		if (timeout_val <= 0)
		{
				spin_unlock_irqrestore(&devc->lock,flags);
			    return 0;
		}
		outb(data[i], PORT(HOST_DATA));
	}
	spin_unlock_irqrestore(&devc->lock,flags);
	return 1;
}