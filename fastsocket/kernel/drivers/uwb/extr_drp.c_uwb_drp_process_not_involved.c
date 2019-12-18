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
struct uwb_rc_evt_drp {int dummy; } ;
struct uwb_rc {int dummy; } ;
struct uwb_mas_bm {int dummy; } ;
struct uwb_ie_drp {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  uwb_drp_handle_all_conflict_rsv (struct uwb_rc*,struct uwb_rc_evt_drp*,struct uwb_ie_drp*,struct uwb_mas_bm*) ; 
 int /*<<< orphan*/  uwb_drp_ie_to_bm (struct uwb_mas_bm*,struct uwb_ie_drp*) ; 

__attribute__((used)) static void uwb_drp_process_not_involved(struct uwb_rc *rc,
					 struct uwb_rc_evt_drp *drp_evt, 
					 struct uwb_ie_drp *drp_ie)
{
	struct uwb_mas_bm mas;
	
	uwb_drp_ie_to_bm(&mas, drp_ie);
	uwb_drp_handle_all_conflict_rsv(rc, drp_evt, drp_ie, &mas);
}