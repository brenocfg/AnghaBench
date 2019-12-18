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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct lpfc_hba {int dummy; } ;
struct lpfc_fcf_rec {int addr_mode; int flag; int /*<<< orphan*/  vlan_id; } ;
struct fcf_record {int dummy; } ;

/* Variables and functions */
 int RECORD_VALID ; 
 int /*<<< orphan*/  __lpfc_update_fcf_record_pri (struct lpfc_hba*,int /*<<< orphan*/ ,struct fcf_record*) ; 
 int /*<<< orphan*/  bf_get (int /*<<< orphan*/ ,struct fcf_record*) ; 
 int /*<<< orphan*/  lpfc_copy_fcf_record (struct lpfc_fcf_rec*,struct fcf_record*) ; 
 int /*<<< orphan*/  lpfc_fcf_record_fcf_index ; 

__attribute__((used)) static void
__lpfc_update_fcf_record(struct lpfc_hba *phba, struct lpfc_fcf_rec *fcf_rec,
		       struct fcf_record *new_fcf_record, uint32_t addr_mode,
		       uint16_t vlan_id, uint32_t flag)
{
	/* Copy the fields from the HBA's FCF record */
	lpfc_copy_fcf_record(fcf_rec, new_fcf_record);
	/* Update other fields of driver FCF record */
	fcf_rec->addr_mode = addr_mode;
	fcf_rec->vlan_id = vlan_id;
	fcf_rec->flag |= (flag | RECORD_VALID);
	__lpfc_update_fcf_record_pri(phba,
		bf_get(lpfc_fcf_record_fcf_index, new_fcf_record),
				 new_fcf_record);
}