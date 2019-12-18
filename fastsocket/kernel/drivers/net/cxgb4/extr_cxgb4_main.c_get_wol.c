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
struct net_device {int dummy; } ;
struct ethtool_wolinfo {int supported; int /*<<< orphan*/  sopass; int /*<<< orphan*/  wolopts; } ;
struct TYPE_2__ {int /*<<< orphan*/  wol; } ;

/* Variables and functions */
 int WAKE_BCAST ; 
 int WAKE_MAGIC ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* netdev2adap (struct net_device*) ; 

__attribute__((used)) static void get_wol(struct net_device *dev, struct ethtool_wolinfo *wol)
{
	wol->supported = WAKE_BCAST | WAKE_MAGIC;
	wol->wolopts = netdev2adap(dev)->wol;
	memset(&wol->sopass, 0, sizeof(wol->sopass));
}