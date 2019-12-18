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
struct net_bridge_port {scalar_t__ designated_cost; scalar_t__ port_id; scalar_t__ designated_port; int /*<<< orphan*/  designated_bridge; int /*<<< orphan*/  designated_root; struct net_bridge* br; } ;
struct net_bridge {scalar_t__ root_path_cost; int /*<<< orphan*/  bridge_id; int /*<<< orphan*/  designated_root; } ;

/* Variables and functions */
 scalar_t__ br_is_designated_port (struct net_bridge_port const*) ; 
 int memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int br_should_become_designated_port(const struct net_bridge_port *p)
{
	struct net_bridge *br;
	int t;

	br = p->br;
	if (br_is_designated_port(p))
		return 1;

	if (memcmp(&p->designated_root, &br->designated_root, 8))
		return 1;

	if (br->root_path_cost < p->designated_cost)
		return 1;
	else if (br->root_path_cost > p->designated_cost)
		return 0;

	t = memcmp(&br->bridge_id, &p->designated_bridge, 8);
	if (t < 0)
		return 1;
	else if (t > 0)
		return 0;

	if (p->port_id < p->designated_port)
		return 1;

	return 0;
}