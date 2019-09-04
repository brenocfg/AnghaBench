#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vlan_parent_ref ;
typedef  int u_int32_t ;
struct ifnet {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  verbose; } ;
struct TYPE_5__ {scalar_t__ vlp_signature; struct ifnet* vlp_ifp; int /*<<< orphan*/  vlp_retain_count; } ;

/* Variables and functions */
 int /*<<< orphan*/  FREE (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_VLAN ; 
 int OSDecrementAtomic (int /*<<< orphan*/ *) ; 
 scalar_t__ VLP_SIGNATURE ; 
 TYPE_3__* g_vlan ; 
 char* ifnet_name (struct ifnet*) ; 
 int /*<<< orphan*/  ifnet_unit (struct ifnet*) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vlan_parent_release(vlan_parent_ref vlp)
{
    u_int32_t		old_retain_count;

    if (vlp->vlp_signature != VLP_SIGNATURE) {
	panic("vlan_parent_release: signature is bad\n");
    }
    old_retain_count = OSDecrementAtomic(&vlp->vlp_retain_count);
    switch (old_retain_count) {
    case 0:
	panic("vlan_parent_release: retain count is 0\n");
	break;
    case 1:
	if (g_vlan->verbose) {
	    struct ifnet * ifp = vlp->vlp_ifp;
	    printf("vlan_parent_release(%s%d)\n", ifnet_name(ifp),
		   ifnet_unit(ifp));
	}
	vlp->vlp_signature = 0;
	FREE(vlp, M_VLAN);
	break;
    default:
	break;
    }
    return;
}