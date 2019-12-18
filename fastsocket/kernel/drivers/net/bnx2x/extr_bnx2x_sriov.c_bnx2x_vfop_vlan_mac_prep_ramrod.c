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
struct bnx2x_vlan_mac_data {int /*<<< orphan*/  cmd; int /*<<< orphan*/  vlan_mac_flags; } ;
struct bnx2x_vlan_mac_ramrod_params {int /*<<< orphan*/  ramrod_flags; struct bnx2x_vlan_mac_data user_req; } ;
struct bnx2x_vfop_vlan_mac_flags {scalar_t__ add; scalar_t__ dont_consume; scalar_t__ single_cmd; scalar_t__ drv_only; } ;

/* Variables and functions */
 int /*<<< orphan*/  BNX2X_DONT_CONSUME_CAM_CREDIT ; 
 int /*<<< orphan*/  BNX2X_VLAN_MAC_ADD ; 
 int /*<<< orphan*/  BNX2X_VLAN_MAC_DEL ; 
 int /*<<< orphan*/  RAMROD_DRV_CLR_ONLY ; 
 int /*<<< orphan*/  RAMROD_EXEC ; 
 int /*<<< orphan*/  memset (struct bnx2x_vlan_mac_ramrod_params*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bnx2x_vfop_vlan_mac_prep_ramrod(struct bnx2x_vlan_mac_ramrod_params *ramrod,
				struct bnx2x_vfop_vlan_mac_flags *flags)
{
	struct bnx2x_vlan_mac_data *ureq = &ramrod->user_req;

	memset(ramrod, 0, sizeof(*ramrod));

	/* ramrod flags */
	if (flags->drv_only)
		set_bit(RAMROD_DRV_CLR_ONLY, &ramrod->ramrod_flags);
	if (flags->single_cmd)
		set_bit(RAMROD_EXEC, &ramrod->ramrod_flags);

	/* mac_vlan flags */
	if (flags->dont_consume)
		set_bit(BNX2X_DONT_CONSUME_CAM_CREDIT, &ureq->vlan_mac_flags);

	/* cmd */
	ureq->cmd = flags->add ? BNX2X_VLAN_MAC_ADD : BNX2X_VLAN_MAC_DEL;
}