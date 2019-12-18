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
struct sk_buff {int dummy; } ;
struct manager {int /*<<< orphan*/  ch; int /*<<< orphan*/  options; int /*<<< orphan*/  sendq; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MGR_PH_ACTIVE ; 
 int /*<<< orphan*/  MISDN_ID_ANY ; 
 int /*<<< orphan*/  PH_ACTIVATE_REQ ; 
 int /*<<< orphan*/  _queue_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_send (struct manager*) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
mgr_send_down(struct manager *mgr, struct sk_buff *skb)
{
	skb_queue_tail(&mgr->sendq, skb);
	if (!test_bit(MGR_PH_ACTIVE, &mgr->options)) {
		_queue_data(&mgr->ch, PH_ACTIVATE_REQ, MISDN_ID_ANY, 0,
		    NULL, GFP_KERNEL);
	} else {
		do_send(mgr);
	}
}