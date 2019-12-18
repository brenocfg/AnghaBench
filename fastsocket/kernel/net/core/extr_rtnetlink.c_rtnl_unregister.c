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
struct TYPE_2__ {int /*<<< orphan*/ * dumpit; int /*<<< orphan*/ * doit; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ENOENT ; 
 int RTNL_FAMILY_MAX ; 
 int rtm_msgindex (int) ; 
 TYPE_1__** rtnl_msg_handlers ; 

int rtnl_unregister(int protocol, int msgtype)
{
	int msgindex;

	BUG_ON(protocol < 0 || protocol > RTNL_FAMILY_MAX);
	msgindex = rtm_msgindex(msgtype);

	if (rtnl_msg_handlers[protocol] == NULL)
		return -ENOENT;

	rtnl_msg_handlers[protocol][msgindex].doit = NULL;
	rtnl_msg_handlers[protocol][msgindex].dumpit = NULL;

	return 0;
}