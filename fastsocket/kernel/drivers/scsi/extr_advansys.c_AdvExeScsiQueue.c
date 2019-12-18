#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ chip_type; TYPE_1__* icq_sp; int /*<<< orphan*/  carr_pending_cnt; TYPE_1__* carr_freelist; int /*<<< orphan*/  iop_base; } ;
struct TYPE_8__ {scalar_t__ target_id; int scsiq_rptr; int areq_vpa; void* carr_pa; void* next_vpa; void* carr_va; void* scsiq_ptr; int /*<<< orphan*/  a_flag; int /*<<< orphan*/  done_status; int /*<<< orphan*/  host_status; } ;
typedef  int /*<<< orphan*/  AdvPortAddr ;
typedef  TYPE_1__ ADV_SCSI_REQ_Q ;
typedef  int ADV_PADDR ;
typedef  TYPE_2__ ADV_DVC_VAR ;
typedef  TYPE_1__ ADV_CARR_T ;

/* Variables and functions */
 int ADV_BUSY ; 
 scalar_t__ ADV_CHIP_ASC3550 ; 
 scalar_t__ ADV_CHIP_ASC38C0800 ; 
 scalar_t__ ADV_CHIP_ASC38C1600 ; 
 int ADV_ERROR ; 
 scalar_t__ ADV_MAX_TID ; 
 int /*<<< orphan*/  ADV_SCSIQ_DONE ; 
 int ADV_SUCCESS ; 
 int /*<<< orphan*/  ADV_TICKLE_A ; 
 int /*<<< orphan*/  ADV_TICKLE_NOP ; 
 scalar_t__ ADV_U32_TO_VADDR (int /*<<< orphan*/ ) ; 
 int ADV_VADDR_TO_U32 (TYPE_1__*) ; 
 int ASC_CQ_STOPPER ; 
 int /*<<< orphan*/  AdvWriteByteRegister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AdvWriteDWordRegister (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  IOPB_TICKLE ; 
 int /*<<< orphan*/  IOPDW_COMMA ; 
 int /*<<< orphan*/  QD_WITH_ERROR ; 
 int /*<<< orphan*/  QHSTA_M_INVALID_DEVICE ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  le32_to_cpu (void*) ; 
 int virt_to_bus (TYPE_1__*) ; 

__attribute__((used)) static int AdvExeScsiQueue(ADV_DVC_VAR *asc_dvc, ADV_SCSI_REQ_Q *scsiq)
{
	AdvPortAddr iop_base;
	ADV_PADDR req_paddr;
	ADV_CARR_T *new_carrp;

	/*
	 * The ADV_SCSI_REQ_Q 'target_id' field should never exceed ADV_MAX_TID.
	 */
	if (scsiq->target_id > ADV_MAX_TID) {
		scsiq->host_status = QHSTA_M_INVALID_DEVICE;
		scsiq->done_status = QD_WITH_ERROR;
		return ADV_ERROR;
	}

	iop_base = asc_dvc->iop_base;

	/*
	 * Allocate a carrier ensuring at least one carrier always
	 * remains on the freelist and initialize fields.
	 */
	if ((new_carrp = asc_dvc->carr_freelist) == NULL) {
		return ADV_BUSY;
	}
	asc_dvc->carr_freelist = (ADV_CARR_T *)
	    ADV_U32_TO_VADDR(le32_to_cpu(new_carrp->next_vpa));
	asc_dvc->carr_pending_cnt++;

	/*
	 * Set the carrier to be a stopper by setting 'next_vpa'
	 * to the stopper value. The current stopper will be changed
	 * below to point to the new stopper.
	 */
	new_carrp->next_vpa = cpu_to_le32(ASC_CQ_STOPPER);

	/*
	 * Clear the ADV_SCSI_REQ_Q done flag.
	 */
	scsiq->a_flag &= ~ADV_SCSIQ_DONE;

	req_paddr = virt_to_bus(scsiq);
	BUG_ON(req_paddr & 31);
	/* Wait for assertion before making little-endian */
	req_paddr = cpu_to_le32(req_paddr);

	/* Save virtual and physical address of ADV_SCSI_REQ_Q and carrier. */
	scsiq->scsiq_ptr = cpu_to_le32(ADV_VADDR_TO_U32(scsiq));
	scsiq->scsiq_rptr = req_paddr;

	scsiq->carr_va = cpu_to_le32(ADV_VADDR_TO_U32(asc_dvc->icq_sp));
	/*
	 * Every ADV_CARR_T.carr_pa is byte swapped to little-endian
	 * order during initialization.
	 */
	scsiq->carr_pa = asc_dvc->icq_sp->carr_pa;

	/*
	 * Use the current stopper to send the ADV_SCSI_REQ_Q command to
	 * the microcode. The newly allocated stopper will become the new
	 * stopper.
	 */
	asc_dvc->icq_sp->areq_vpa = req_paddr;

	/*
	 * Set the 'next_vpa' pointer for the old stopper to be the
	 * physical address of the new stopper. The RISC can only
	 * follow physical addresses.
	 */
	asc_dvc->icq_sp->next_vpa = new_carrp->carr_pa;

	/*
	 * Set the host adapter stopper pointer to point to the new carrier.
	 */
	asc_dvc->icq_sp = new_carrp;

	if (asc_dvc->chip_type == ADV_CHIP_ASC3550 ||
	    asc_dvc->chip_type == ADV_CHIP_ASC38C0800) {
		/*
		 * Tickle the RISC to tell it to read its Command Queue Head pointer.
		 */
		AdvWriteByteRegister(iop_base, IOPB_TICKLE, ADV_TICKLE_A);
		if (asc_dvc->chip_type == ADV_CHIP_ASC3550) {
			/*
			 * Clear the tickle value. In the ASC-3550 the RISC flag
			 * command 'clr_tickle_a' does not work unless the host
			 * value is cleared.
			 */
			AdvWriteByteRegister(iop_base, IOPB_TICKLE,
					     ADV_TICKLE_NOP);
		}
	} else if (asc_dvc->chip_type == ADV_CHIP_ASC38C1600) {
		/*
		 * Notify the RISC a carrier is ready by writing the physical
		 * address of the new carrier stopper to the COMMA register.
		 */
		AdvWriteDWordRegister(iop_base, IOPDW_COMMA,
				      le32_to_cpu(new_carrp->carr_pa));
	}

	return ADV_SUCCESS;
}