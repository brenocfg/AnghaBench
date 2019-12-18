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
typedef  int /*<<< orphan*/  uint16_t ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __bdx_vlan_rx_vid (struct net_device*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void bdx_vlan_rx_add_vid(struct net_device *ndev, uint16_t vid)
{
	__bdx_vlan_rx_vid(ndev, vid, 1);
}