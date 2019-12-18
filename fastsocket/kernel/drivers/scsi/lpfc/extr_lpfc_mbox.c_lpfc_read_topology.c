#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct lpfc_sli {int dummy; } ;
struct lpfc_hba {struct lpfc_sli sli; } ;
struct lpfc_dmabuf {int /*<<< orphan*/  phys; int /*<<< orphan*/  list; } ;
struct TYPE_12__ {int /*<<< orphan*/  bdeSize; } ;
struct TYPE_13__ {TYPE_2__ f; } ;
struct TYPE_14__ {int /*<<< orphan*/  addrLow; int /*<<< orphan*/  addrHigh; TYPE_3__ tus; } ;
struct TYPE_15__ {TYPE_4__ lilpBde64; } ;
struct TYPE_16__ {TYPE_5__ varReadTop; } ;
struct TYPE_17__ {int /*<<< orphan*/  mbxOwner; TYPE_6__ un; int /*<<< orphan*/  mbxCommand; } ;
struct TYPE_11__ {TYPE_7__ mb; } ;
struct TYPE_18__ {int /*<<< orphan*/ * context1; TYPE_1__ u; } ;
typedef  TYPE_7__ MAILBOX_t ;
typedef  TYPE_8__ LPFC_MBOXQ_t ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LPFC_ALPA_MAP_SIZE ; 
 int /*<<< orphan*/  MBX_READ_TOPOLOGY ; 
 int /*<<< orphan*/  OWN_HOST ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  putPaddrHigh (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  putPaddrLow (int /*<<< orphan*/ ) ; 

int
lpfc_read_topology(struct lpfc_hba *phba, LPFC_MBOXQ_t *pmb,
		   struct lpfc_dmabuf *mp)
{
	MAILBOX_t *mb;
	struct lpfc_sli *psli;

	psli = &phba->sli;
	mb = &pmb->u.mb;
	memset(pmb, 0, sizeof (LPFC_MBOXQ_t));

	INIT_LIST_HEAD(&mp->list);
	mb->mbxCommand = MBX_READ_TOPOLOGY;
	mb->un.varReadTop.lilpBde64.tus.f.bdeSize = LPFC_ALPA_MAP_SIZE;
	mb->un.varReadTop.lilpBde64.addrHigh = putPaddrHigh(mp->phys);
	mb->un.varReadTop.lilpBde64.addrLow = putPaddrLow(mp->phys);

	/* Save address for later completion and set the owner to host so that
	 * the FW knows this mailbox is available for processing.
	 */
	pmb->context1 = (uint8_t *)mp;
	mb->mbxOwner = OWN_HOST;
	return (0);
}