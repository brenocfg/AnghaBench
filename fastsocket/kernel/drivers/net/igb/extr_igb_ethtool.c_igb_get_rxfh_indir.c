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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct igb_adapter {int /*<<< orphan*/ * rss_indir_tbl; } ;

/* Variables and functions */
 int IGB_RETA_SIZE ; 
 struct igb_adapter* netdev_priv (struct net_device*) ; 

__attribute__((used)) static int igb_get_rxfh_indir(struct net_device *netdev, u32 *indir)
{
	struct igb_adapter *adapter = netdev_priv(netdev);
	int i;

	for (i = 0; i < IGB_RETA_SIZE; i++)
		indir[i] = adapter->rss_indir_tbl[i];

	return 0;
}