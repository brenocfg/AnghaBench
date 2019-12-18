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
struct tsi108_prv_data {int /*<<< orphan*/  timer; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 scalar_t__ CHECK_PHY_INTERVAL ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct tsi108_prv_data* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tsi108_check_phy (struct net_device*) ; 
 int /*<<< orphan*/  tsi108_check_rxring (struct net_device*) ; 

__attribute__((used)) static void tsi108_timed_checker(unsigned long dev_ptr)
{
	struct net_device *dev = (struct net_device *)dev_ptr;
	struct tsi108_prv_data *data = netdev_priv(dev);

	tsi108_check_phy(dev);
	tsi108_check_rxring(dev);
	mod_timer(&data->timer, jiffies + CHECK_PHY_INTERVAL);
}