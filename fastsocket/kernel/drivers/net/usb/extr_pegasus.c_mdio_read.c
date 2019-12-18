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
typedef  scalar_t__ u16 ;
struct net_device {int dummy; } ;
typedef  int /*<<< orphan*/  pegasus_t ;

/* Variables and functions */
 scalar_t__ netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  read_mii_word (int /*<<< orphan*/ *,int,int,scalar_t__*) ; 

__attribute__((used)) static int mdio_read(struct net_device *dev, int phy_id, int loc)
{
	pegasus_t *pegasus = (pegasus_t *) netdev_priv(dev);
	u16 res;

	read_mii_word(pegasus, phy_id, loc, &res);
	return (int)res;
}