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
typedef  int /*<<< orphan*/  u_char ;
struct sk_buff {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
struct l3_process {int /*<<< orphan*/  callref; int /*<<< orphan*/  st; } ;

/* Variables and functions */
 int /*<<< orphan*/  IE_FACILITY ; 
 int check_infoelements (struct l3_process*,struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * findie (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ie_FACILITY ; 
 int /*<<< orphan*/  l3dss1_parse_facility (int /*<<< orphan*/ ,struct l3_process*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l3dss1_std_ie_err (struct l3_process*,int) ; 

__attribute__((used)) static void
l3dss1_facility(struct l3_process *pc, u_char pr, void *arg)
{
	struct sk_buff *skb = arg;
	int ret;
	
	ret = check_infoelements(pc, skb, ie_FACILITY);
	l3dss1_std_ie_err(pc, ret);
 	  {
		u_char *p;
		if ((p = findie(skb->data, skb->len, IE_FACILITY, 0)))
			l3dss1_parse_facility(pc->st, pc, pc->callref, p);
	}
}