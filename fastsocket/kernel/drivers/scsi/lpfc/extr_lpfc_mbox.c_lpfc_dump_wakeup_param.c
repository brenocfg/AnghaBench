#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct lpfc_hba {int dummy; } ;
struct TYPE_9__ {int cv; scalar_t__ resp_offset; scalar_t__ co; int /*<<< orphan*/  word_cnt; int /*<<< orphan*/  region_id; scalar_t__ entry_index; int /*<<< orphan*/  type; } ;
struct TYPE_10__ {TYPE_2__ varDmp; } ;
struct TYPE_11__ {TYPE_3__ un; int /*<<< orphan*/  mbxOwner; int /*<<< orphan*/  mbxCommand; } ;
struct TYPE_8__ {TYPE_4__ mb; } ;
struct TYPE_12__ {void* context2; TYPE_1__ u; } ;
typedef  TYPE_4__ MAILBOX_t ;
typedef  TYPE_5__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMP_NV_PARAMS ; 
 int /*<<< orphan*/  MBX_DUMP_MEMORY ; 
 int /*<<< orphan*/  OWN_HOST ; 
 int /*<<< orphan*/  WAKE_UP_PARMS_REGION_ID ; 
 int /*<<< orphan*/  WAKE_UP_PARMS_WORD_SIZE ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

void
lpfc_dump_wakeup_param(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb)
{
	MAILBOX_t *mb;
	void *ctx;

	mb = &pmb->u.mb;
	/* Save context so that we can restore after memset */
	ctx = pmb->context2;

	/* Setup to dump VPD region */
	memset(pmb, 0, sizeof(LPFC_MBOXQ_t));
	mb->mbxCommand = MBX_DUMP_MEMORY;
	mb->mbxOwner = OWN_HOST;
	mb->un.varDmp.cv = 1;
	mb->un.varDmp.type = DMP_NV_PARAMS;
	mb->un.varDmp.entry_index = 0;
	mb->un.varDmp.region_id = WAKE_UP_PARMS_REGION_ID;
	mb->un.varDmp.word_cnt = WAKE_UP_PARMS_WORD_SIZE;
	mb->un.varDmp.co = 0;
	mb->un.varDmp.resp_offset = 0;
	pmb->context2 = ctx;
	return;
}