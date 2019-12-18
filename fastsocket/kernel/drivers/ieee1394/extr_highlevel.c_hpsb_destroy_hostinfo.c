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
struct hpsb_host {int dummy; } ;
struct hpsb_highlevel {int /*<<< orphan*/  host_info_lock; } ;
struct hl_host_info {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 struct hl_host_info* hl_get_hostinfo (struct hpsb_highlevel*,struct hpsb_host*) ; 
 int /*<<< orphan*/  kfree (struct hl_host_info*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void hpsb_destroy_hostinfo(struct hpsb_highlevel *hl, struct hpsb_host *host)
{
	struct hl_host_info *hi;

	hi = hl_get_hostinfo(hl, host);
	if (hi) {
		unsigned long flags;
		write_lock_irqsave(&hl->host_info_lock, flags);
		list_del(&hi->list);
		write_unlock_irqrestore(&hl->host_info_lock, flags);
		kfree(hi);
	}
	return;
}