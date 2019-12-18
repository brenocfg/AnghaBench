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
struct port {int /*<<< orphan*/ * slave; } ;
struct bonding {int dummy; } ;

/* Variables and functions */
 struct bonding* bond_get_bond_by_slave (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline struct bonding *__get_bond_by_port(struct port *port)
{
	if (port->slave == NULL) {
		return NULL;
	}

	return bond_get_bond_by_slave(port->slave);
}