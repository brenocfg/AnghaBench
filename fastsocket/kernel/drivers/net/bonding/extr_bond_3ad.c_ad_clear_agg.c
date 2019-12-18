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
struct aggregator {int is_individual; int /*<<< orphan*/  aggregator_identifier; scalar_t__ num_of_ports; scalar_t__ is_active; int /*<<< orphan*/ * lag_ports; scalar_t__ transmit_state; scalar_t__ receive_state; scalar_t__ partner_oper_aggregator_key; scalar_t__ partner_system_priority; int /*<<< orphan*/  partner_system; scalar_t__ actor_oper_aggregator_key; scalar_t__ actor_admin_aggregator_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  null_mac_addr ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ad_clear_agg(struct aggregator *aggregator)
{
	if (aggregator) {
		aggregator->is_individual = false;
		aggregator->actor_admin_aggregator_key = 0;
		aggregator->actor_oper_aggregator_key = 0;
		aggregator->partner_system = null_mac_addr;
		aggregator->partner_system_priority = 0;
		aggregator->partner_oper_aggregator_key = 0;
		aggregator->receive_state = 0;
		aggregator->transmit_state = 0;
		aggregator->lag_ports = NULL;
		aggregator->is_active = 0;
		aggregator->num_of_ports = 0;
		pr_debug("LAG %d was cleared\n", aggregator->aggregator_identifier);
	}
}