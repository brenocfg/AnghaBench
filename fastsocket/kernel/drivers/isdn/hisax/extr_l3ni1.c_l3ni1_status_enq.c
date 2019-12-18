#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int cause; } ;
struct l3_process {TYPE_1__ para; } ;

/* Variables and functions */
 int check_infoelements (struct l3_process*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ie_STATUS_ENQUIRY ; 
 int /*<<< orphan*/  l3ni1_status_send (struct l3_process*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l3ni1_std_ie_err (struct l3_process*,int) ; 

__attribute__((used)) static void
l3ni1_status_enq(struct l3_process *pc, u_char pr, void *arg)
{
	int ret;
	struct sk_buff *skb = arg;

	ret = check_infoelements(pc, skb, ie_STATUS_ENQUIRY);
	l3ni1_std_ie_err(pc, ret);
	pc->para.cause = 30; /* response to STATUS_ENQUIRY */
        l3ni1_status_send(pc, pr, NULL);
}