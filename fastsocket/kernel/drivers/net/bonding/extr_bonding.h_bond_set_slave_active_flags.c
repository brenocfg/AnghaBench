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
struct slave {TYPE_1__* dev; int /*<<< orphan*/  state; } ;
struct TYPE_2__ {int priv_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOND_STATE_ACTIVE ; 
 int IFF_SLAVE_INACTIVE ; 
 int IFF_SLAVE_NEEDARP ; 

__attribute__((used)) static inline void bond_set_slave_active_flags(struct slave *slave)
{
	slave->state = BOND_STATE_ACTIVE;
	slave->dev->priv_flags &= ~(IFF_SLAVE_INACTIVE | IFF_SLAVE_NEEDARP);
}