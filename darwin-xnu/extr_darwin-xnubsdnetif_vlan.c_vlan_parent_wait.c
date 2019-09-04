#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vlan_parent_ref ;
struct ifnet {int dummy; } ;
struct TYPE_8__ {scalar_t__ verbose; } ;
struct TYPE_7__ {struct ifnet* vlp_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  PZERO ; 
 TYPE_6__* g_vlan ; 
 char* ifnet_name (struct ifnet*) ; 
 char* ifnet_unit (struct ifnet*) ; 
 int /*<<< orphan*/  msleep (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char const*) ; 
 int /*<<< orphan*/  vlan_lck_mtx ; 
 scalar_t__ vlan_parent_flags_change_in_progress (TYPE_1__*) ; 
 int /*<<< orphan*/  vlan_parent_flags_set_change_in_progress (TYPE_1__*) ; 

__attribute__((used)) static void
vlan_parent_wait(vlan_parent_ref vlp, const char * msg)
{
    int		waited = 0;

    /* other add/remove/multicast-change in progress */
    while (vlan_parent_flags_change_in_progress(vlp)) {
	if (g_vlan->verbose) {
	    struct ifnet * ifp = vlp->vlp_ifp;

	    printf("%s%d: %s msleep\n", ifnet_name(ifp), ifnet_unit(ifp), msg);
	}
	waited = 1;
	(void)msleep(vlp, vlan_lck_mtx, PZERO, msg, 0);
    }
    /* prevent other vlan parent remove/add from taking place */
    vlan_parent_flags_set_change_in_progress(vlp);
    if (g_vlan->verbose && waited) {
	struct ifnet * ifp = vlp->vlp_ifp;

	printf("%s%d: %s woke up\n", ifnet_name(ifp), ifnet_unit(ifp), msg);
    }
    return;
}