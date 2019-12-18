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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  InitBoard (struct net_device*) ; 
 int /*<<< orphan*/  StopSONIC (struct net_device*) ; 

__attribute__((used)) static void ibmlana_set_multicast_list(struct net_device *dev)
{
	/* first stop the SONIC... */
	StopSONIC(dev);
	/* ...then reinit it with the new flags */
	InitBoard(dev);
}