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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u64 ;
struct ehea_port {TYPE_1__* mc_list; } ;
struct ehea_mc_list {int /*<<< orphan*/  list; int /*<<< orphan*/  macaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  H_REG_BCMC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehea_error (char*) ; 
 int /*<<< orphan*/  ehea_multicast_reg_helper (struct ehea_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct ehea_mc_list*) ; 
 struct ehea_mc_list* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ehea_add_multicast_entry(struct ehea_port *port, u8 *mc_mac_addr)
{
	struct ehea_mc_list *ehea_mcl_entry;
	u64 hret;

	ehea_mcl_entry = kzalloc(sizeof(*ehea_mcl_entry), GFP_ATOMIC);
	if (!ehea_mcl_entry) {
		ehea_error("no mem for mcl_entry");
		return;
	}

	INIT_LIST_HEAD(&ehea_mcl_entry->list);

	memcpy(&ehea_mcl_entry->macaddr, mc_mac_addr, ETH_ALEN);

	hret = ehea_multicast_reg_helper(port, ehea_mcl_entry->macaddr,
					 H_REG_BCMC);
	if (!hret)
		list_add(&ehea_mcl_entry->list, &port->mc_list->list);
	else {
		ehea_error("failed registering mcast MAC");
		kfree(ehea_mcl_entry);
	}
}