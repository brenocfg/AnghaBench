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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u32 ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  stat_string; } ;

/* Variables and functions */
 int ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 129 
#define  ETH_SS_TEST 128 
 int NETXEN_NIC_STATS_LEN ; 
 int NETXEN_NIC_TEST_LEN ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* netxen_nic_gstrings_stats ; 
 int /*<<< orphan*/ * netxen_nic_gstrings_test ; 

__attribute__((used)) static void
netxen_nic_get_strings(struct net_device *dev, u32 stringset, u8 * data)
{
	int index;

	switch (stringset) {
	case ETH_SS_TEST:
		memcpy(data, *netxen_nic_gstrings_test,
		       NETXEN_NIC_TEST_LEN * ETH_GSTRING_LEN);
		break;
	case ETH_SS_STATS:
		for (index = 0; index < NETXEN_NIC_STATS_LEN; index++) {
			memcpy(data + index * ETH_GSTRING_LEN,
			       netxen_nic_gstrings_stats[index].stat_string,
			       ETH_GSTRING_LEN);
		}
		break;
	}
}