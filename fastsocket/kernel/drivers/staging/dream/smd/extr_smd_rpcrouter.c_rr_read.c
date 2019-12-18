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

/* Variables and functions */
 int EIO ; 
 int rpcrouter_need_len ; 
 int /*<<< orphan*/  rpcrouter_wake_lock ; 
 int /*<<< orphan*/  smd_channel ; 
 int /*<<< orphan*/  smd_lock ; 
 int smd_read (int /*<<< orphan*/ ,void*,int) ; 
 int smd_read_avail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smd_wait ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rr_read(void *data, int len)
{
	int rc;
	unsigned long flags;
//	printk("rr_read() %d\n", len);
	for(;;) {
		spin_lock_irqsave(&smd_lock, flags);
		if (smd_read_avail(smd_channel) >= len) {
			rc = smd_read(smd_channel, data, len);
			spin_unlock_irqrestore(&smd_lock, flags);
			if (rc == len)
				return 0;
			else
				return -EIO;
		}
		rpcrouter_need_len = len;
		wake_unlock(&rpcrouter_wake_lock);
		spin_unlock_irqrestore(&smd_lock, flags);

//		printk("rr_read: waiting (%d)\n", len);
		wait_event(smd_wait, smd_read_avail(smd_channel) >= len);
	}
	return 0;
}