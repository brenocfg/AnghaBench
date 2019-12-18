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
struct slave {unsigned long last_arp_rx; TYPE_1__* dev; } ;
struct bonding {int dummy; } ;
struct TYPE_2__ {unsigned long last_rx; } ;

/* Variables and functions */
 scalar_t__ slave_do_arp_validate (struct bonding*,struct slave*) ; 

__attribute__((used)) static inline unsigned long slave_last_rx(struct bonding *bond,
					struct slave *slave)
{
	if (slave_do_arp_validate(bond, slave))
		return slave->last_arp_rx;

	return slave->dev->last_rx;
}