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
 int /*<<< orphan*/  stmmac_schedule (struct net_device*) ; 

__attribute__((used)) static void stmmac_timer_handler(void *data)
{
	struct net_device *dev = (struct net_device *)data;

	stmmac_schedule(dev);

	return;
}