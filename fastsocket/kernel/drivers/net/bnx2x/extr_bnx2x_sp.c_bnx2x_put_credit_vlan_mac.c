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
struct bnx2x_vlan_mac_obj {struct bnx2x_credit_pool_obj* vlans_pool; struct bnx2x_credit_pool_obj* macs_pool; } ;
struct bnx2x_credit_pool_obj {int /*<<< orphan*/  (* get ) (struct bnx2x_credit_pool_obj*,int) ;int /*<<< orphan*/  (* put ) (struct bnx2x_credit_pool_obj*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct bnx2x_credit_pool_obj*,int) ; 
 int /*<<< orphan*/  stub2 (struct bnx2x_credit_pool_obj*,int) ; 
 int /*<<< orphan*/  stub3 (struct bnx2x_credit_pool_obj*,int) ; 

__attribute__((used)) static bool bnx2x_put_credit_vlan_mac(struct bnx2x_vlan_mac_obj *o)
{
	struct bnx2x_credit_pool_obj *mp = o->macs_pool;
	struct bnx2x_credit_pool_obj *vp = o->vlans_pool;

	if (!mp->put(mp, 1))
		return false;

	if (!vp->put(vp, 1)) {
		mp->get(mp, 1);
		return false;
	}

	return true;
}