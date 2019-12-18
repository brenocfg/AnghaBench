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
struct ipx_interface {int /*<<< orphan*/  node; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipx_interfaces ; 
 int /*<<< orphan*/  ipx_interfaces_lock ; 
 struct ipx_interface* ipx_primary_net ; 
 scalar_t__ ipxcfg_auto_select_primary ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ipxitf_insert(struct ipx_interface *intrfc)
{
	spin_lock_bh(&ipx_interfaces_lock);
	list_add_tail(&intrfc->node, &ipx_interfaces);
	spin_unlock_bh(&ipx_interfaces_lock);

	if (ipxcfg_auto_select_primary && !ipx_primary_net)
		ipx_primary_net = intrfc;
}