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
struct TYPE_3__ {unsigned char qdioac1; int /*<<< orphan*/  sch_token; } ;
struct TYPE_4__ {int sch_no; } ;
struct qdio_irq {TYPE_1__ ssqd_desc; TYPE_2__ schid; } ;

/* Variables and functions */
 unsigned char AC1_SIGA_INPUT_NEEDED ; 
 unsigned char AC1_SIGA_OUTPUT_NEEDED ; 
 unsigned char AC1_SIGA_SYNC_NEEDED ; 
 int /*<<< orphan*/  DBF_ERROR (char*,int) ; 
 int /*<<< orphan*/  DBF_EVENT (char*,unsigned char) ; 
 int /*<<< orphan*/  check_and_setup_qebsm (struct qdio_irq*,unsigned char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_ac_flags (struct qdio_irq*,unsigned char) ; 
 int qdio_setup_get_ssqd (struct qdio_irq*,TYPE_2__*,int /*<<< orphan*/ *) ; 

void qdio_setup_ssqd_info(struct qdio_irq *irq_ptr)
{
	unsigned char qdioac;
	int rc;

	rc = qdio_setup_get_ssqd(irq_ptr, &irq_ptr->schid, NULL);
	if (rc) {
		DBF_ERROR("%4x ssqd ERR", irq_ptr->schid.sch_no);
		DBF_ERROR("rc:%x", rc);
		/* all flags set, worst case */
		qdioac = AC1_SIGA_INPUT_NEEDED | AC1_SIGA_OUTPUT_NEEDED |
			 AC1_SIGA_SYNC_NEEDED;
	} else
		qdioac = irq_ptr->ssqd_desc.qdioac1;

	check_and_setup_qebsm(irq_ptr, qdioac, irq_ptr->ssqd_desc.sch_token);
	process_ac_flags(irq_ptr, qdioac);
	DBF_EVENT("qdioac:%4x", qdioac);
}