#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* ifbond_ref ;
typedef  TYPE_3__* bondport_ref ;
struct TYPE_16__ {scalar_t__ verbose; } ;
struct TYPE_15__ {scalar_t__ po_selected; int /*<<< orphan*/  po_media_info; TYPE_1__* po_lag; TYPE_2__* po_bond; } ;
struct TYPE_14__ {scalar_t__ ifb_mode; TYPE_1__* ifb_active_lag; } ;
struct TYPE_13__ {scalar_t__ lag_active_media; } ;

/* Variables and functions */
 scalar_t__ IF_BOND_MODE_LACP ; 
 int /*<<< orphan*/  LAEventMediaChange ; 
 scalar_t__ SelectedState_UNSELECTED ; 
 int /*<<< orphan*/  bondport_disable_distributing (TYPE_3__*) ; 
 int /*<<< orphan*/  bondport_enable_distributing (TYPE_3__*) ; 
 int /*<<< orphan*/  bondport_get_name (TYPE_3__*) ; 
 int /*<<< orphan*/  bondport_mux_machine (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bondport_periodic_transmit_machine (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bondport_receive_machine (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bondport_set_selected (TYPE_3__*,scalar_t__) ; 
 TYPE_4__* g_bond ; 
 char* link_speed (scalar_t__) ; 
 scalar_t__ media_active (int /*<<< orphan*/ *) ; 
 scalar_t__ media_full_duplex (int /*<<< orphan*/ *) ; 
 scalar_t__ media_speed (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timestamp_printf (char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
bondport_link_status_changed(bondport_ref p)
{
    ifbond_ref	bond = p->po_bond;

    if (g_bond->verbose) {
	if (media_active(&p->po_media_info)) {
	    timestamp_printf("[%s] Link UP %d Mbit/s %s duplex\n", 
			     bondport_get_name(p),
			     media_speed(&p->po_media_info),
			     media_full_duplex(&p->po_media_info) 
			     ? "full" : "half");
	}
	else {
	    timestamp_printf("[%s] Link DOWN\n", bondport_get_name(p));
	}
    }
    if (bond->ifb_mode == IF_BOND_MODE_LACP) {
	if (media_active(&p->po_media_info)
	    && bond->ifb_active_lag != NULL
	    && p->po_lag == bond->ifb_active_lag
	    && p->po_selected != SelectedState_UNSELECTED) {
	    if (media_speed(&p->po_media_info) != p->po_lag->lag_active_media) {
		if (g_bond->verbose) {
		    timestamp_printf("[%s] Port speed %d differs from LAG %d\n",
				     bondport_get_name(p),
				     media_speed(&p->po_media_info),
				     link_speed(p->po_lag->lag_active_media));
		}
		bondport_set_selected(p, SelectedState_UNSELECTED);
	    }
	}
	bondport_receive_machine(p, LAEventMediaChange, NULL);
	bondport_mux_machine(p, LAEventMediaChange, NULL);
	bondport_periodic_transmit_machine(p, LAEventMediaChange, NULL);
    }
    else {
	if (media_active(&p->po_media_info)) {
	    bondport_enable_distributing(p);
	}
	else {
	    bondport_disable_distributing(p);
	}
    }
    return;
}