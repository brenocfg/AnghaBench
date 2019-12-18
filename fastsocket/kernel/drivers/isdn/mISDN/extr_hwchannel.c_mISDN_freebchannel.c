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
struct bchannel {scalar_t__ rcount; int /*<<< orphan*/  rqueue; } ;

/* Variables and functions */
 int /*<<< orphan*/  flush_scheduled_work () ; 
 int /*<<< orphan*/  mISDN_clear_bchannel (struct bchannel*) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 

int
mISDN_freebchannel(struct bchannel *ch)
{
	mISDN_clear_bchannel(ch);
	skb_queue_purge(&ch->rqueue);
	ch->rcount = 0;
	flush_scheduled_work();
	return 0;
}