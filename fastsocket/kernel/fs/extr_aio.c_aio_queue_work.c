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
struct kioctx {int /*<<< orphan*/  wq; int /*<<< orphan*/  wait; } ;

/* Variables and functions */
 int HZ ; 
 int /*<<< orphan*/  aio_wq ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  smp_mb () ; 
 scalar_t__ waitqueue_active (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void aio_queue_work(struct kioctx * ctx)
{
	unsigned long timeout;
	/*
	 * if someone is waiting, get the work started right
	 * away, otherwise, use a longer delay
	 */
	smp_mb();
	if (waitqueue_active(&ctx->wait))
		timeout = 1;
	else
		timeout = HZ/10;
	queue_delayed_work(aio_wq, &ctx->wq, timeout);
}