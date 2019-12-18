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
struct net_bridge_port {TYPE_1__* br; int /*<<< orphan*/  message_age_timer; int /*<<< orphan*/  designated_port; int /*<<< orphan*/  designated_bridge; int /*<<< orphan*/  designated_cost; int /*<<< orphan*/  designated_root; } ;
struct br_config_bpdu {scalar_t__ message_age; int /*<<< orphan*/  port_id; int /*<<< orphan*/  bridge_id; int /*<<< orphan*/  root_path_cost; int /*<<< orphan*/  root; } ;
struct TYPE_2__ {scalar_t__ max_age; } ;

/* Variables and functions */
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static inline void br_record_config_information(struct net_bridge_port *p,
						const struct br_config_bpdu *bpdu)
{
	p->designated_root = bpdu->root;
	p->designated_cost = bpdu->root_path_cost;
	p->designated_bridge = bpdu->bridge_id;
	p->designated_port = bpdu->port_id;

	mod_timer(&p->message_age_timer, jiffies
		  + (p->br->max_age - bpdu->message_age));
}