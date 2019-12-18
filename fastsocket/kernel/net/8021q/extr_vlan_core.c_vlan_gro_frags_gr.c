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
struct vlan_group {int dummy; } ;
struct napi_struct {int dummy; } ;
typedef  int /*<<< orphan*/  gro_result_t ;

/* Variables and functions */
 int /*<<< orphan*/  __vlan_gro_frags_gr (struct napi_struct*,struct vlan_group*,unsigned int) ; 

gro_result_t vlan_gro_frags_gr(struct napi_struct *napi,
			       struct vlan_group *grp, unsigned int vlan_tci)
{
	return __vlan_gro_frags_gr(napi, grp, vlan_tci);
}