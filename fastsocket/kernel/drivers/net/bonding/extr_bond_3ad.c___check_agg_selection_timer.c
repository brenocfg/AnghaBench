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
struct port {int dummy; } ;
struct bonding {int dummy; } ;
struct TYPE_2__ {scalar_t__ agg_select_timer; } ;

/* Variables and functions */
 TYPE_1__ BOND_AD_INFO (struct bonding*) ; 
 struct bonding* __get_bond_by_port (struct port*) ; 

__attribute__((used)) static inline int __check_agg_selection_timer(struct port *port)
{
	struct bonding *bond = __get_bond_by_port(port);

	if (bond == NULL) {
		return 0;
	}

	return BOND_AD_INFO(bond).agg_select_timer ? 1 : 0;
}