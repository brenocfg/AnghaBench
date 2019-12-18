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
struct notifier_block {int dummy; } ;

/* Variables and functions */
#define  MEM_CANCEL_OFFLINE 133 
#define  MEM_CANCEL_ONLINE 132 
#define  MEM_GOING_OFFLINE 131 
#define  MEM_GOING_ONLINE 130 
#define  MEM_OFFLINE 129 
#define  MEM_ONLINE 128 
 int NOTIFY_BAD ; 
 int NOTIFY_OK ; 
 int /*<<< orphan*/  ehca_gen_err (char*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk_timed_ratelimit (unsigned long*,int) ; 
 int /*<<< orphan*/  shca_list ; 
 int /*<<< orphan*/  shca_list_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int ehca_mem_notifier(struct notifier_block *nb,
			     unsigned long action, void *data)
{
	static unsigned long ehca_dmem_warn_time;
	unsigned long flags;

	switch (action) {
	case MEM_CANCEL_OFFLINE:
	case MEM_CANCEL_ONLINE:
	case MEM_ONLINE:
	case MEM_OFFLINE:
		return NOTIFY_OK;
	case MEM_GOING_ONLINE:
	case MEM_GOING_OFFLINE:
		/* only ok if no hca is attached to the lpar */
		spin_lock_irqsave(&shca_list_lock, flags);
		if (list_empty(&shca_list)) {
			spin_unlock_irqrestore(&shca_list_lock, flags);
			return NOTIFY_OK;
		} else {
			spin_unlock_irqrestore(&shca_list_lock, flags);
			if (printk_timed_ratelimit(&ehca_dmem_warn_time,
						   30 * 1000))
				ehca_gen_err("DMEM operations are not allowed"
					     "in conjunction with eHCA");
			return NOTIFY_BAD;
		}
	}
	return NOTIFY_OK;
}