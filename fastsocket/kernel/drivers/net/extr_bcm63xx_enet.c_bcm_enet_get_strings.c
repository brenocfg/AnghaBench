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
 int BCM_ENET_STATS_LEN ; 
 int ETH_GSTRING_LEN ; 
#define  ETH_SS_STATS 128 
 TYPE_1__* bcm_enet_gstrings_stats ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bcm_enet_get_strings(struct net_device *netdev,
				 u32 stringset, u8 *data)
{
	int i;

	switch (stringset) {
	case ETH_SS_STATS:
		for (i = 0; i < BCM_ENET_STATS_LEN; i++) {
			memcpy(data + i * ETH_GSTRING_LEN,
			       bcm_enet_gstrings_stats[i].stat_string,
			       ETH_GSTRING_LEN);
		}
		break;
	}
}