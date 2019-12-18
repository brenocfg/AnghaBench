#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint16_t ;
struct TYPE_3__ {struct lpfc_fcf_pri* fcf_pri; } ;
struct lpfc_hba {TYPE_1__ fcf; } ;
struct TYPE_4__ {size_t fcf_index; int /*<<< orphan*/  priority; } ;
struct lpfc_fcf_pri {TYPE_2__ fcf_rec; } ;
struct fcf_record {int /*<<< orphan*/  fip_priority; } ;

/* Variables and functions */

__attribute__((used)) static void
__lpfc_update_fcf_record_pri(struct lpfc_hba *phba, uint16_t fcf_index,
				 struct fcf_record *new_fcf_record
				 )
{
	struct lpfc_fcf_pri *fcf_pri;

	fcf_pri = &phba->fcf.fcf_pri[fcf_index];
	fcf_pri->fcf_rec.fcf_index = fcf_index;
	/* FCF record priority */
	fcf_pri->fcf_rec.priority = new_fcf_record->fip_priority;

}