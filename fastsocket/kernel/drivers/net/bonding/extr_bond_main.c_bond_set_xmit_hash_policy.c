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
struct TYPE_2__ {int xmit_policy; } ;
struct bonding {int /*<<< orphan*/  xmit_hash_policy; TYPE_1__ params; } ;

/* Variables and functions */
#define  BOND_XMIT_POLICY_LAYER2 130 
#define  BOND_XMIT_POLICY_LAYER23 129 
#define  BOND_XMIT_POLICY_LAYER34 128 
 int /*<<< orphan*/  bond_xmit_hash_policy_l2 ; 
 int /*<<< orphan*/  bond_xmit_hash_policy_l23 ; 
 int /*<<< orphan*/  bond_xmit_hash_policy_l34 ; 

__attribute__((used)) static void bond_set_xmit_hash_policy(struct bonding *bond)
{
	switch (bond->params.xmit_policy) {
	case BOND_XMIT_POLICY_LAYER23:
		bond->xmit_hash_policy = bond_xmit_hash_policy_l23;
		break;
	case BOND_XMIT_POLICY_LAYER34:
		bond->xmit_hash_policy = bond_xmit_hash_policy_l34;
		break;
	case BOND_XMIT_POLICY_LAYER2:
	default:
		bond->xmit_hash_policy = bond_xmit_hash_policy_l2;
		break;
	}
}