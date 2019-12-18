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
struct TYPE_2__ {int /*<<< orphan*/  vlan_mac_flags; } ;
struct bnx2x_vlan_mac_ramrod_params {TYPE_1__ user_req; } ;
struct bnx2x_vfop_vlan_mac_flags {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_ETH_MAC ; 
 int /*<<< orphan*/  bnx2x_vfop_vlan_mac_prep_ramrod (struct bnx2x_vlan_mac_ramrod_params*,struct bnx2x_vfop_vlan_mac_flags*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
bnx2x_vfop_mac_prep_ramrod(struct bnx2x_vlan_mac_ramrod_params *ramrod,
			   struct bnx2x_vfop_vlan_mac_flags *flags)
{
	bnx2x_vfop_vlan_mac_prep_ramrod(ramrod, flags);
	set_bit(BNX2X_ETH_MAC, &ramrod->user_req.vlan_mac_flags);
}