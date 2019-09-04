#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vlan_parent_ref ;
struct ifnet {int dummy; } ;
struct TYPE_6__ {int vlp_retain_count; int /*<<< orphan*/  vlp_signature; struct ifnet* vlp_ifp; int /*<<< orphan*/  vlp_vlan_list; int /*<<< orphan*/  vlp_devmtu; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  FREE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int IF_HWASSIST_VLAN_MTU ; 
 int IF_HWASSIST_VLAN_TAGGING ; 
 int /*<<< orphan*/  LIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  M_VLAN ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  VLP_SIGNATURE ; 
 TYPE_1__* _MALLOC (int,int /*<<< orphan*/ ,int) ; 
 char* ifnet_name (struct ifnet*) ; 
 int ifnet_offload (struct ifnet*) ; 
 int ifnet_unit (struct ifnet*) ; 
 int /*<<< orphan*/  printf (char*,char*,int,int) ; 
 int siocgifdevmtu (struct ifnet*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlan_parent_flags_set_supports_vlan_mtu (TYPE_1__*) ; 

__attribute__((used)) static int
vlan_parent_create(struct ifnet * p, vlan_parent_ref * ret_vlp)
{
    int			error;
    vlan_parent_ref	vlp;

    *ret_vlp = NULL;
    vlp = _MALLOC(sizeof(*vlp), M_VLAN, M_WAITOK | M_ZERO);
    if (vlp == NULL) {
	return (ENOMEM);
    }
    error = siocgifdevmtu(p, &vlp->vlp_devmtu);
    if (error != 0) {
	printf("vlan_parent_create (%s%d): siocgifdevmtu failed, %d\n",
	       ifnet_name(p), ifnet_unit(p), error);
	FREE(vlp, M_VLAN);
	return (error);
    }
    LIST_INIT(&vlp->vlp_vlan_list);
    vlp->vlp_ifp = p;
    vlp->vlp_retain_count = 1;
    vlp->vlp_signature = VLP_SIGNATURE;
    if (ifnet_offload(p)
	& (IF_HWASSIST_VLAN_MTU | IF_HWASSIST_VLAN_TAGGING)) {
	vlan_parent_flags_set_supports_vlan_mtu(vlp);
    }
    *ret_vlp = vlp;
    return (0);
}