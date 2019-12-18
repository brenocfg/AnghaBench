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
typedef  int u32 ;
struct typhoon {int dummy; } ;
struct net_device {int flags; scalar_t__ mc_count; struct dev_mc_list* mc_list; } ;
struct dev_mc_list {int /*<<< orphan*/  dmi_addr; struct dev_mc_list* next; } ;
struct cmd_desc {int parm1; void* parm3; void* parm2; } ;
typedef  int /*<<< orphan*/  mc_filter ;
typedef  int __le16 ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int IFF_ALLMULTI ; 
 int IFF_PROMISC ; 
 int /*<<< orphan*/  INIT_COMMAND_NO_RESPONSE (struct cmd_desc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPHOON_CMD_SET_MULTICAST_HASH ; 
 int /*<<< orphan*/  TYPHOON_CMD_SET_RX_FILTER ; 
 int TYPHOON_MCAST_HASH_SET ; 
 int TYPHOON_RX_FILTER_ALL_MCAST ; 
 int TYPHOON_RX_FILTER_BROADCAST ; 
 int TYPHOON_RX_FILTER_DIRECTED ; 
 int TYPHOON_RX_FILTER_MCAST_HASH ; 
 int TYPHOON_RX_FILTER_PROMISCOUS ; 
 void* cpu_to_le32 (int) ; 
 int ether_crc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ multicast_filter_limit ; 
 struct typhoon* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  typhoon_issue_command (struct typhoon*,int,struct cmd_desc*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
typhoon_set_rx_mode(struct net_device *dev)
{
	struct typhoon *tp = netdev_priv(dev);
	struct cmd_desc xp_cmd;
	u32 mc_filter[2];
	__le16 filter;

	filter = TYPHOON_RX_FILTER_DIRECTED | TYPHOON_RX_FILTER_BROADCAST;
	if(dev->flags & IFF_PROMISC) {
		filter |= TYPHOON_RX_FILTER_PROMISCOUS;
	} else if((dev->mc_count > multicast_filter_limit) ||
		  (dev->flags & IFF_ALLMULTI)) {
		/* Too many to match, or accept all multicasts. */
		filter |= TYPHOON_RX_FILTER_ALL_MCAST;
	} else if(dev->mc_count) {
		struct dev_mc_list *mclist;
		int i;

		memset(mc_filter, 0, sizeof(mc_filter));
		for(i = 0, mclist = dev->mc_list; mclist && i < dev->mc_count;
		    i++, mclist = mclist->next) {
			int bit = ether_crc(ETH_ALEN, mclist->dmi_addr) & 0x3f;
			mc_filter[bit >> 5] |= 1 << (bit & 0x1f);
		}

		INIT_COMMAND_NO_RESPONSE(&xp_cmd,
					 TYPHOON_CMD_SET_MULTICAST_HASH);
		xp_cmd.parm1 = TYPHOON_MCAST_HASH_SET;
		xp_cmd.parm2 = cpu_to_le32(mc_filter[0]);
		xp_cmd.parm3 = cpu_to_le32(mc_filter[1]);
		typhoon_issue_command(tp, 1, &xp_cmd, 0, NULL);

		filter |= TYPHOON_RX_FILTER_MCAST_HASH;
	}

	INIT_COMMAND_NO_RESPONSE(&xp_cmd, TYPHOON_CMD_SET_RX_FILTER);
	xp_cmd.parm1 = filter;
	typhoon_issue_command(tp, 1, &xp_cmd, 0, NULL);
}