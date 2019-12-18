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
struct sk_buff {int dummy; } ;
struct genl_info {TYPE_1__* genlhdr; } ;
struct TYPE_2__ {int cmd; } ;

/* Variables and functions */
 int ENOTSUPP ; 
#define  NET_DM_CMD_START 129 
#define  NET_DM_CMD_STOP 128 
 int /*<<< orphan*/  TRACE_OFF ; 
 int /*<<< orphan*/  TRACE_ON ; 
 int set_all_monitor_traces (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int net_dm_cmd_trace(struct sk_buff *skb,
			struct genl_info *info)
{
	switch (info->genlhdr->cmd) {
	case NET_DM_CMD_START:
		return set_all_monitor_traces(TRACE_ON);
		break;
	case NET_DM_CMD_STOP:
		return set_all_monitor_traces(TRACE_OFF);
		break;
	}

	return -ENOTSUPP;
}