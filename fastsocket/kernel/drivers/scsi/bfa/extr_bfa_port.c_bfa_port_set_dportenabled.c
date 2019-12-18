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
struct bfa_port_s {int /*<<< orphan*/  dport_enabled; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;

/* Variables and functions */

void
bfa_port_set_dportenabled(struct bfa_port_s *port, bfa_boolean_t enabled)
{
	port->dport_enabled = enabled;
}