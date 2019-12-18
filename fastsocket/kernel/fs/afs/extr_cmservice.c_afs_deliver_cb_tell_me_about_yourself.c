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
struct sk_buff {scalar_t__ len; } ;
struct afs_call {int /*<<< orphan*/  work; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  AFS_CALL_REPLYING ; 
 int EBADMSG ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRXAFSCB_TellMeAboutYourself ; 
 int /*<<< orphan*/  _enter (char*,scalar_t__,int) ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afs_deliver_cb_tell_me_about_yourself(struct afs_call *call,
						 struct sk_buff *skb, bool last)
{
	_enter(",{%u},%d", skb->len, last);

	if (skb->len > 0)
		return -EBADMSG;
	if (!last)
		return 0;

	/* no unmarshalling required */
	call->state = AFS_CALL_REPLYING;

	INIT_WORK(&call->work, SRXAFSCB_TellMeAboutYourself);
	schedule_work(&call->work);
	return 0;
}