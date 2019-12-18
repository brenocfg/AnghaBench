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
struct net_device {int dummy; } ;
struct cp_private {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CpCmd ; 
 int RxChkSum ; 
 int cpr16 (int /*<<< orphan*/ ) ; 
 struct cp_private* netdev_priv (struct net_device*) ; 

__attribute__((used)) static u32 cp_get_rx_csum(struct net_device *dev)
{
	struct cp_private *cp = netdev_priv(dev);
	return (cpr16(CpCmd) & RxChkSum) ? 1 : 0;
}