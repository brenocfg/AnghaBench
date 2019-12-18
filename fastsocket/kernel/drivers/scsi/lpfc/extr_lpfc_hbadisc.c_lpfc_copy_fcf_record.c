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
struct lpfc_fcf_rec {void** switch_name; int /*<<< orphan*/  priority; void* fcf_indx; void** mac_addr; void** fabric_name; } ;
struct fcf_record {int /*<<< orphan*/  fip_priority; } ;

/* Variables and functions */
 void* bf_get (int /*<<< orphan*/ ,struct fcf_record*) ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_0 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_1 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_2 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_3 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_4 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_5 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_6 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fab_name_7 ; 
 int /*<<< orphan*/  lpfc_fcf_record_fcf_index ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_0 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_1 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_2 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_3 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_4 ; 
 int /*<<< orphan*/  lpfc_fcf_record_mac_5 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_0 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_1 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_2 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_3 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_4 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_5 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_6 ; 
 int /*<<< orphan*/  lpfc_fcf_record_switch_name_7 ; 

__attribute__((used)) static void
lpfc_copy_fcf_record(struct lpfc_fcf_rec *fcf_rec,
		     struct fcf_record *new_fcf_record)
{
	/* Fabric name */
	fcf_rec->fabric_name[0] =
		bf_get(lpfc_fcf_record_fab_name_0, new_fcf_record);
	fcf_rec->fabric_name[1] =
		bf_get(lpfc_fcf_record_fab_name_1, new_fcf_record);
	fcf_rec->fabric_name[2] =
		bf_get(lpfc_fcf_record_fab_name_2, new_fcf_record);
	fcf_rec->fabric_name[3] =
		bf_get(lpfc_fcf_record_fab_name_3, new_fcf_record);
	fcf_rec->fabric_name[4] =
		bf_get(lpfc_fcf_record_fab_name_4, new_fcf_record);
	fcf_rec->fabric_name[5] =
		bf_get(lpfc_fcf_record_fab_name_5, new_fcf_record);
	fcf_rec->fabric_name[6] =
		bf_get(lpfc_fcf_record_fab_name_6, new_fcf_record);
	fcf_rec->fabric_name[7] =
		bf_get(lpfc_fcf_record_fab_name_7, new_fcf_record);
	/* Mac address */
	fcf_rec->mac_addr[0] = bf_get(lpfc_fcf_record_mac_0, new_fcf_record);
	fcf_rec->mac_addr[1] = bf_get(lpfc_fcf_record_mac_1, new_fcf_record);
	fcf_rec->mac_addr[2] = bf_get(lpfc_fcf_record_mac_2, new_fcf_record);
	fcf_rec->mac_addr[3] = bf_get(lpfc_fcf_record_mac_3, new_fcf_record);
	fcf_rec->mac_addr[4] = bf_get(lpfc_fcf_record_mac_4, new_fcf_record);
	fcf_rec->mac_addr[5] = bf_get(lpfc_fcf_record_mac_5, new_fcf_record);
	/* FCF record index */
	fcf_rec->fcf_indx = bf_get(lpfc_fcf_record_fcf_index, new_fcf_record);
	/* FCF record priority */
	fcf_rec->priority = new_fcf_record->fip_priority;
	/* Switch name */
	fcf_rec->switch_name[0] =
		bf_get(lpfc_fcf_record_switch_name_0, new_fcf_record);
	fcf_rec->switch_name[1] =
		bf_get(lpfc_fcf_record_switch_name_1, new_fcf_record);
	fcf_rec->switch_name[2] =
		bf_get(lpfc_fcf_record_switch_name_2, new_fcf_record);
	fcf_rec->switch_name[3] =
		bf_get(lpfc_fcf_record_switch_name_3, new_fcf_record);
	fcf_rec->switch_name[4] =
		bf_get(lpfc_fcf_record_switch_name_4, new_fcf_record);
	fcf_rec->switch_name[5] =
		bf_get(lpfc_fcf_record_switch_name_5, new_fcf_record);
	fcf_rec->switch_name[6] =
		bf_get(lpfc_fcf_record_switch_name_6, new_fcf_record);
	fcf_rec->switch_name[7] =
		bf_get(lpfc_fcf_record_switch_name_7, new_fcf_record);
}