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
struct TYPE_6__ {int /*<<< orphan*/  queue_lock; } ;
struct TYPE_5__ {scalar_t__ errors; TYPE_1__* rq_disk; } ;
struct TYPE_4__ {char* disk_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EIO ; 
 scalar_t__ MAX_ERRORS ; 
 int /*<<< orphan*/ * do_hd ; 
 int /*<<< orphan*/  hd_end_request_cur (int /*<<< orphan*/ ) ; 
 TYPE_3__* hd_queue ; 
 TYPE_2__* hd_req ; 
 int /*<<< orphan*/  hd_request () ; 
 int /*<<< orphan*/  printk (char*,char*) ; 
 int reset ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hd_times_out(unsigned long dummy)
{
	char *name;

	do_hd = NULL;

	if (!hd_req)
		return;

	spin_lock_irq(hd_queue->queue_lock);
	reset = 1;
	name = hd_req->rq_disk->disk_name;
	printk("%s: timeout\n", name);
	if (++hd_req->errors >= MAX_ERRORS) {
#ifdef DEBUG
		printk("%s: too many errors\n", name);
#endif
		hd_end_request_cur(-EIO);
	}
	hd_request();
	spin_unlock_irq(hd_queue->queue_lock);
}