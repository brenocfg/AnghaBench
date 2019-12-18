#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ushort ;
typedef  size_t uchar ;
struct asc_board {size_t* sdtr_data; int queue_full; size_t* queue_full_cnt; } ;
struct TYPE_13__ {int pci_fix_asyn_xfer; scalar_t__* sdtr_period_tbl; size_t min_sdtr_index; size_t max_sdtr_index; int init_sdtr; int sdtr_done; int pci_fix_asyn_xfer_always; scalar_t__* cur_dvc_qng; int queue_full_or_busy; size_t* max_dvc_qng; int /*<<< orphan*/  iop_base; struct asc_board* drv_ptr; } ;
struct TYPE_12__ {int remain_sg_entry_cnt; size_t next_sg_index; TYPE_3__* sg_head; } ;
struct TYPE_11__ {int queue_cnt; int /*<<< orphan*/ * sg_list; } ;
struct TYPE_10__ {size_t sg_head_qp; int cntl; int seq_no; size_t q_no; scalar_t__ sg_cur_list_cnt; scalar_t__ sg_list_cnt; } ;
struct TYPE_9__ {scalar_t__ msg_type; scalar_t__ msg_req; scalar_t__ msg_len; scalar_t__ req_ack_offset; scalar_t__ xfer_period; scalar_t__ wdtr_width; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  TYPE_1__ EXT_MSG ;
typedef  TYPE_2__ ASC_SG_LIST_Q ;
typedef  TYPE_3__ ASC_SG_HEAD ;
typedef  TYPE_4__ ASC_SCSI_Q ;
typedef  int ASC_SCSI_BIT_ID_TYPE ;
typedef  TYPE_5__ ASC_DVC_VAR ;

/* Variables and functions */
 scalar_t__ ASCV_CURCDB_B ; 
 int /*<<< orphan*/  ASCV_HALTCODE_W ; 
 scalar_t__ ASCV_MAX_DVC_QNG_BEG ; 
 scalar_t__ ASCV_MSGIN_BEG ; 
 scalar_t__ ASCV_MSGOUT_BEG ; 
 scalar_t__ ASCV_REQ_SG_LIST_QP ; 
 scalar_t__ ASCV_SCSIBUSY_B ; 
 scalar_t__ ASC_HALT_CHK_CONDITION ; 
 scalar_t__ ASC_HALT_DISABLE_ASYN_USE_SYN_FIX ; 
 scalar_t__ ASC_HALT_ENABLE_ASYN_USE_SYN_FIX ; 
 scalar_t__ ASC_HALT_EXTMSG_IN ; 
 scalar_t__ ASC_HALT_HOST_COPY_SG_LIST_TO_RISC ; 
 scalar_t__ ASC_HALT_SDTR_REJECTED ; 
 scalar_t__ ASC_HALT_SS_QUEUE_FULL ; 
 int ASC_MAX_SG_LIST ; 
 size_t ASC_MIN_TAGGED_CMD ; 
 scalar_t__ ASC_QADR_BEG ; 
 size_t ASC_QLINK_END ; 
 scalar_t__ ASC_QNO_TO_QADDR (size_t) ; 
 scalar_t__ ASC_SCSIQ_B_CNTL ; 
 scalar_t__ ASC_SCSIQ_B_FIRST_SG_WK_QP ; 
 scalar_t__ ASC_SCSIQ_B_FWD ; 
 scalar_t__ ASC_SCSIQ_B_SG_WK_QP ; 
 scalar_t__ ASC_SCSIQ_B_STATUS ; 
 scalar_t__ ASC_SCSIQ_B_TAG_CODE ; 
 scalar_t__ ASC_SCSIQ_B_TARGET_IX ; 
 scalar_t__ ASC_SCSIQ_D_SRBPTR ; 
 scalar_t__ ASC_SCSIQ_SCSI_STATUS ; 
 scalar_t__ ASC_SCSIQ_SGHD_CPY_BEG ; 
 scalar_t__ ASC_SGQ_LIST_BEG ; 
 scalar_t__ ASC_SG_LIST_PER_Q ; 
 scalar_t__ ASC_SRB2SCSIQ (int /*<<< orphan*/ ) ; 
 scalar_t__ ASC_SYN_MAX_OFFSET ; 
 size_t ASC_TAG_FLAG_DISABLE_ASYN_USE_SYN_FIX ; 
 size_t ASC_TAG_FLAG_DISABLE_DISCONNECT ; 
 scalar_t__ ASC_TID_TO_TARGET_ID (size_t) ; 
 size_t ASC_TIX_TO_TID (size_t) ; 
 int /*<<< orphan*/  ASC_U32_TO_VADDR (int /*<<< orphan*/ ) ; 
 size_t ASYN_SDTR_DATA_FIX_PCI_REV_AB ; 
 size_t AscCalSDTRData (TYPE_5__*,scalar_t__,scalar_t__) ; 
 size_t AscGetMCodeInitSDTRAtID (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  AscMemDWordCopyPtrToLram (int /*<<< orphan*/ ,scalar_t__,size_t*,scalar_t__) ; 
 int /*<<< orphan*/  AscMemWordCopyPtrFromLram (int /*<<< orphan*/ ,scalar_t__,size_t*,int) ; 
 int /*<<< orphan*/  AscMemWordCopyPtrToLram (int /*<<< orphan*/ ,scalar_t__,size_t*,int) ; 
 int /*<<< orphan*/  AscMsgOutSDTR (TYPE_5__*,scalar_t__,size_t) ; 
 void* AscReadLramByte (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  AscReadLramDWord (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ AscReadLramWord (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AscSetChipSDTR (int /*<<< orphan*/ ,size_t,size_t) ; 
 int /*<<< orphan*/  AscWriteLramByte (int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  AscWriteLramWord (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 scalar_t__ EXTENDED_MESSAGE ; 
 scalar_t__ EXTENDED_SDTR ; 
 scalar_t__ EXTENDED_WDTR ; 
 int FALSE ; 
 scalar_t__ MESSAGE_REJECT ; 
 scalar_t__ MS_SDTR_LEN ; 
 scalar_t__ MS_WDTR_LEN ; 
 int QCSG_SG_XFER_END ; 
 int QCSG_SG_XFER_LIST ; 
 int QCSG_SG_XFER_MORE ; 
 size_t QC_MSG_OUT ; 
 size_t QC_REQ_SENSE ; 
 size_t QS_BUSY ; 
 size_t QS_READY ; 
 size_t SAM_STAT_TASK_SET_FULL ; 
 int TRUE ; 

__attribute__((used)) static int AscIsrChipHalted(ASC_DVC_VAR *asc_dvc)
{
	EXT_MSG ext_msg;
	EXT_MSG out_msg;
	ushort halt_q_addr;
	int sdtr_accept;
	ushort int_halt_code;
	ASC_SCSI_BIT_ID_TYPE scsi_busy;
	ASC_SCSI_BIT_ID_TYPE target_id;
	PortAddr iop_base;
	uchar tag_code;
	uchar q_status;
	uchar halt_qp;
	uchar sdtr_data;
	uchar target_ix;
	uchar q_cntl, tid_no;
	uchar cur_dvc_qng;
	uchar asyn_sdtr;
	uchar scsi_status;
	struct asc_board *boardp;

	BUG_ON(!asc_dvc->drv_ptr);
	boardp = asc_dvc->drv_ptr;

	iop_base = asc_dvc->iop_base;
	int_halt_code = AscReadLramWord(iop_base, ASCV_HALTCODE_W);

	halt_qp = AscReadLramByte(iop_base, ASCV_CURCDB_B);
	halt_q_addr = ASC_QNO_TO_QADDR(halt_qp);
	target_ix = AscReadLramByte(iop_base,
				    (ushort)(halt_q_addr +
					     (ushort)ASC_SCSIQ_B_TARGET_IX));
	q_cntl = AscReadLramByte(iop_base,
			    (ushort)(halt_q_addr + (ushort)ASC_SCSIQ_B_CNTL));
	tid_no = ASC_TIX_TO_TID(target_ix);
	target_id = (uchar)ASC_TID_TO_TARGET_ID(tid_no);
	if (asc_dvc->pci_fix_asyn_xfer & target_id) {
		asyn_sdtr = ASYN_SDTR_DATA_FIX_PCI_REV_AB;
	} else {
		asyn_sdtr = 0;
	}
	if (int_halt_code == ASC_HALT_DISABLE_ASYN_USE_SYN_FIX) {
		if (asc_dvc->pci_fix_asyn_xfer & target_id) {
			AscSetChipSDTR(iop_base, 0, tid_no);
			boardp->sdtr_data[tid_no] = 0;
		}
		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		return (0);
	} else if (int_halt_code == ASC_HALT_ENABLE_ASYN_USE_SYN_FIX) {
		if (asc_dvc->pci_fix_asyn_xfer & target_id) {
			AscSetChipSDTR(iop_base, asyn_sdtr, tid_no);
			boardp->sdtr_data[tid_no] = asyn_sdtr;
		}
		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		return (0);
	} else if (int_halt_code == ASC_HALT_EXTMSG_IN) {
		AscMemWordCopyPtrFromLram(iop_base,
					  ASCV_MSGIN_BEG,
					  (uchar *)&ext_msg,
					  sizeof(EXT_MSG) >> 1);

		if (ext_msg.msg_type == EXTENDED_MESSAGE &&
		    ext_msg.msg_req == EXTENDED_SDTR &&
		    ext_msg.msg_len == MS_SDTR_LEN) {
			sdtr_accept = TRUE;
			if ((ext_msg.req_ack_offset > ASC_SYN_MAX_OFFSET)) {

				sdtr_accept = FALSE;
				ext_msg.req_ack_offset = ASC_SYN_MAX_OFFSET;
			}
			if ((ext_msg.xfer_period <
			     asc_dvc->sdtr_period_tbl[asc_dvc->min_sdtr_index])
			    || (ext_msg.xfer_period >
				asc_dvc->sdtr_period_tbl[asc_dvc->
							 max_sdtr_index])) {
				sdtr_accept = FALSE;
				ext_msg.xfer_period =
				    asc_dvc->sdtr_period_tbl[asc_dvc->
							     min_sdtr_index];
			}
			if (sdtr_accept) {
				sdtr_data =
				    AscCalSDTRData(asc_dvc, ext_msg.xfer_period,
						   ext_msg.req_ack_offset);
				if ((sdtr_data == 0xFF)) {

					q_cntl |= QC_MSG_OUT;
					asc_dvc->init_sdtr &= ~target_id;
					asc_dvc->sdtr_done &= ~target_id;
					AscSetChipSDTR(iop_base, asyn_sdtr,
						       tid_no);
					boardp->sdtr_data[tid_no] = asyn_sdtr;
				}
			}
			if (ext_msg.req_ack_offset == 0) {

				q_cntl &= ~QC_MSG_OUT;
				asc_dvc->init_sdtr &= ~target_id;
				asc_dvc->sdtr_done &= ~target_id;
				AscSetChipSDTR(iop_base, asyn_sdtr, tid_no);
			} else {
				if (sdtr_accept && (q_cntl & QC_MSG_OUT)) {
					q_cntl &= ~QC_MSG_OUT;
					asc_dvc->sdtr_done |= target_id;
					asc_dvc->init_sdtr |= target_id;
					asc_dvc->pci_fix_asyn_xfer &=
					    ~target_id;
					sdtr_data =
					    AscCalSDTRData(asc_dvc,
							   ext_msg.xfer_period,
							   ext_msg.
							   req_ack_offset);
					AscSetChipSDTR(iop_base, sdtr_data,
						       tid_no);
					boardp->sdtr_data[tid_no] = sdtr_data;
				} else {
					q_cntl |= QC_MSG_OUT;
					AscMsgOutSDTR(asc_dvc,
						      ext_msg.xfer_period,
						      ext_msg.req_ack_offset);
					asc_dvc->pci_fix_asyn_xfer &=
					    ~target_id;
					sdtr_data =
					    AscCalSDTRData(asc_dvc,
							   ext_msg.xfer_period,
							   ext_msg.
							   req_ack_offset);
					AscSetChipSDTR(iop_base, sdtr_data,
						       tid_no);
					boardp->sdtr_data[tid_no] = sdtr_data;
					asc_dvc->sdtr_done |= target_id;
					asc_dvc->init_sdtr |= target_id;
				}
			}

			AscWriteLramByte(iop_base,
					 (ushort)(halt_q_addr +
						  (ushort)ASC_SCSIQ_B_CNTL),
					 q_cntl);
			AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
			return (0);
		} else if (ext_msg.msg_type == EXTENDED_MESSAGE &&
			   ext_msg.msg_req == EXTENDED_WDTR &&
			   ext_msg.msg_len == MS_WDTR_LEN) {

			ext_msg.wdtr_width = 0;
			AscMemWordCopyPtrToLram(iop_base,
						ASCV_MSGOUT_BEG,
						(uchar *)&ext_msg,
						sizeof(EXT_MSG) >> 1);
			q_cntl |= QC_MSG_OUT;
			AscWriteLramByte(iop_base,
					 (ushort)(halt_q_addr +
						  (ushort)ASC_SCSIQ_B_CNTL),
					 q_cntl);
			AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
			return (0);
		} else {

			ext_msg.msg_type = MESSAGE_REJECT;
			AscMemWordCopyPtrToLram(iop_base,
						ASCV_MSGOUT_BEG,
						(uchar *)&ext_msg,
						sizeof(EXT_MSG) >> 1);
			q_cntl |= QC_MSG_OUT;
			AscWriteLramByte(iop_base,
					 (ushort)(halt_q_addr +
						  (ushort)ASC_SCSIQ_B_CNTL),
					 q_cntl);
			AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
			return (0);
		}
	} else if (int_halt_code == ASC_HALT_CHK_CONDITION) {

		q_cntl |= QC_REQ_SENSE;

		if ((asc_dvc->init_sdtr & target_id) != 0) {

			asc_dvc->sdtr_done &= ~target_id;

			sdtr_data = AscGetMCodeInitSDTRAtID(iop_base, tid_no);
			q_cntl |= QC_MSG_OUT;
			AscMsgOutSDTR(asc_dvc,
				      asc_dvc->
				      sdtr_period_tbl[(sdtr_data >> 4) &
						      (uchar)(asc_dvc->
							      max_sdtr_index -
							      1)],
				      (uchar)(sdtr_data & (uchar)
					      ASC_SYN_MAX_OFFSET));
		}

		AscWriteLramByte(iop_base,
				 (ushort)(halt_q_addr +
					  (ushort)ASC_SCSIQ_B_CNTL), q_cntl);

		tag_code = AscReadLramByte(iop_base,
					   (ushort)(halt_q_addr + (ushort)
						    ASC_SCSIQ_B_TAG_CODE));
		tag_code &= 0xDC;
		if ((asc_dvc->pci_fix_asyn_xfer & target_id)
		    && !(asc_dvc->pci_fix_asyn_xfer_always & target_id)
		    ) {

			tag_code |= (ASC_TAG_FLAG_DISABLE_DISCONNECT
				     | ASC_TAG_FLAG_DISABLE_ASYN_USE_SYN_FIX);

		}
		AscWriteLramByte(iop_base,
				 (ushort)(halt_q_addr +
					  (ushort)ASC_SCSIQ_B_TAG_CODE),
				 tag_code);

		q_status = AscReadLramByte(iop_base,
					   (ushort)(halt_q_addr + (ushort)
						    ASC_SCSIQ_B_STATUS));
		q_status |= (QS_READY | QS_BUSY);
		AscWriteLramByte(iop_base,
				 (ushort)(halt_q_addr +
					  (ushort)ASC_SCSIQ_B_STATUS),
				 q_status);

		scsi_busy = AscReadLramByte(iop_base, (ushort)ASCV_SCSIBUSY_B);
		scsi_busy &= ~target_id;
		AscWriteLramByte(iop_base, (ushort)ASCV_SCSIBUSY_B, scsi_busy);

		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		return (0);
	} else if (int_halt_code == ASC_HALT_SDTR_REJECTED) {

		AscMemWordCopyPtrFromLram(iop_base,
					  ASCV_MSGOUT_BEG,
					  (uchar *)&out_msg,
					  sizeof(EXT_MSG) >> 1);

		if ((out_msg.msg_type == EXTENDED_MESSAGE) &&
		    (out_msg.msg_len == MS_SDTR_LEN) &&
		    (out_msg.msg_req == EXTENDED_SDTR)) {

			asc_dvc->init_sdtr &= ~target_id;
			asc_dvc->sdtr_done &= ~target_id;
			AscSetChipSDTR(iop_base, asyn_sdtr, tid_no);
			boardp->sdtr_data[tid_no] = asyn_sdtr;
		}
		q_cntl &= ~QC_MSG_OUT;
		AscWriteLramByte(iop_base,
				 (ushort)(halt_q_addr +
					  (ushort)ASC_SCSIQ_B_CNTL), q_cntl);
		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		return (0);
	} else if (int_halt_code == ASC_HALT_SS_QUEUE_FULL) {

		scsi_status = AscReadLramByte(iop_base,
					      (ushort)((ushort)halt_q_addr +
						       (ushort)
						       ASC_SCSIQ_SCSI_STATUS));
		cur_dvc_qng =
		    AscReadLramByte(iop_base,
				    (ushort)((ushort)ASC_QADR_BEG +
					     (ushort)target_ix));
		if ((cur_dvc_qng > 0) && (asc_dvc->cur_dvc_qng[tid_no] > 0)) {

			scsi_busy = AscReadLramByte(iop_base,
						    (ushort)ASCV_SCSIBUSY_B);
			scsi_busy |= target_id;
			AscWriteLramByte(iop_base,
					 (ushort)ASCV_SCSIBUSY_B, scsi_busy);
			asc_dvc->queue_full_or_busy |= target_id;

			if (scsi_status == SAM_STAT_TASK_SET_FULL) {
				if (cur_dvc_qng > ASC_MIN_TAGGED_CMD) {
					cur_dvc_qng -= 1;
					asc_dvc->max_dvc_qng[tid_no] =
					    cur_dvc_qng;

					AscWriteLramByte(iop_base,
							 (ushort)((ushort)
								  ASCV_MAX_DVC_QNG_BEG
								  + (ushort)
								  tid_no),
							 cur_dvc_qng);

					/*
					 * Set the device queue depth to the
					 * number of active requests when the
					 * QUEUE FULL condition was encountered.
					 */
					boardp->queue_full |= target_id;
					boardp->queue_full_cnt[tid_no] =
					    cur_dvc_qng;
				}
			}
		}
		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		return (0);
	}
#if CC_VERY_LONG_SG_LIST
	else if (int_halt_code == ASC_HALT_HOST_COPY_SG_LIST_TO_RISC) {
		uchar q_no;
		ushort q_addr;
		uchar sg_wk_q_no;
		uchar first_sg_wk_q_no;
		ASC_SCSI_Q *scsiq;	/* Ptr to driver request. */
		ASC_SG_HEAD *sg_head;	/* Ptr to driver SG request. */
		ASC_SG_LIST_Q scsi_sg_q;	/* Structure written to queue. */
		ushort sg_list_dwords;
		ushort sg_entry_cnt;
		uchar next_qp;
		int i;

		q_no = AscReadLramByte(iop_base, (ushort)ASCV_REQ_SG_LIST_QP);
		if (q_no == ASC_QLINK_END)
			return 0;

		q_addr = ASC_QNO_TO_QADDR(q_no);

		/*
		 * Convert the request's SRB pointer to a host ASC_SCSI_REQ
		 * structure pointer using a macro provided by the driver.
		 * The ASC_SCSI_REQ pointer provides a pointer to the
		 * host ASC_SG_HEAD structure.
		 */
		/* Read request's SRB pointer. */
		scsiq = (ASC_SCSI_Q *)
		    ASC_SRB2SCSIQ(ASC_U32_TO_VADDR(AscReadLramDWord(iop_base,
								    (ushort)
								    (q_addr +
								     ASC_SCSIQ_D_SRBPTR))));

		/*
		 * Get request's first and working SG queue.
		 */
		sg_wk_q_no = AscReadLramByte(iop_base,
					     (ushort)(q_addr +
						      ASC_SCSIQ_B_SG_WK_QP));

		first_sg_wk_q_no = AscReadLramByte(iop_base,
						   (ushort)(q_addr +
							    ASC_SCSIQ_B_FIRST_SG_WK_QP));

		/*
		 * Reset request's working SG queue back to the
		 * first SG queue.
		 */
		AscWriteLramByte(iop_base,
				 (ushort)(q_addr +
					  (ushort)ASC_SCSIQ_B_SG_WK_QP),
				 first_sg_wk_q_no);

		sg_head = scsiq->sg_head;

		/*
		 * Set sg_entry_cnt to the number of SG elements
		 * that will be completed on this interrupt.
		 *
		 * Note: The allocated SG queues contain ASC_MAX_SG_LIST - 1
		 * SG elements. The data_cnt and data_addr fields which
		 * add 1 to the SG element capacity are not used when
		 * restarting SG handling after a halt.
		 */
		if (scsiq->remain_sg_entry_cnt > (ASC_MAX_SG_LIST - 1)) {
			sg_entry_cnt = ASC_MAX_SG_LIST - 1;

			/*
			 * Keep track of remaining number of SG elements that
			 * will need to be handled on the next interrupt.
			 */
			scsiq->remain_sg_entry_cnt -= (ASC_MAX_SG_LIST - 1);
		} else {
			sg_entry_cnt = scsiq->remain_sg_entry_cnt;
			scsiq->remain_sg_entry_cnt = 0;
		}

		/*
		 * Copy SG elements into the list of allocated SG queues.
		 *
		 * Last index completed is saved in scsiq->next_sg_index.
		 */
		next_qp = first_sg_wk_q_no;
		q_addr = ASC_QNO_TO_QADDR(next_qp);
		scsi_sg_q.sg_head_qp = q_no;
		scsi_sg_q.cntl = QCSG_SG_XFER_LIST;
		for (i = 0; i < sg_head->queue_cnt; i++) {
			scsi_sg_q.seq_no = i + 1;
			if (sg_entry_cnt > ASC_SG_LIST_PER_Q) {
				sg_list_dwords = (uchar)(ASC_SG_LIST_PER_Q * 2);
				sg_entry_cnt -= ASC_SG_LIST_PER_Q;
				/*
				 * After very first SG queue RISC FW uses next
				 * SG queue first element then checks sg_list_cnt
				 * against zero and then decrements, so set
				 * sg_list_cnt 1 less than number of SG elements
				 * in each SG queue.
				 */
				scsi_sg_q.sg_list_cnt = ASC_SG_LIST_PER_Q - 1;
				scsi_sg_q.sg_cur_list_cnt =
				    ASC_SG_LIST_PER_Q - 1;
			} else {
				/*
				 * This is the last SG queue in the list of
				 * allocated SG queues. If there are more
				 * SG elements than will fit in the allocated
				 * queues, then set the QCSG_SG_XFER_MORE flag.
				 */
				if (scsiq->remain_sg_entry_cnt != 0) {
					scsi_sg_q.cntl |= QCSG_SG_XFER_MORE;
				} else {
					scsi_sg_q.cntl |= QCSG_SG_XFER_END;
				}
				/* equals sg_entry_cnt * 2 */
				sg_list_dwords = sg_entry_cnt << 1;
				scsi_sg_q.sg_list_cnt = sg_entry_cnt - 1;
				scsi_sg_q.sg_cur_list_cnt = sg_entry_cnt - 1;
				sg_entry_cnt = 0;
			}

			scsi_sg_q.q_no = next_qp;
			AscMemWordCopyPtrToLram(iop_base,
						q_addr + ASC_SCSIQ_SGHD_CPY_BEG,
						(uchar *)&scsi_sg_q,
						sizeof(ASC_SG_LIST_Q) >> 1);

			AscMemDWordCopyPtrToLram(iop_base,
						 q_addr + ASC_SGQ_LIST_BEG,
						 (uchar *)&sg_head->
						 sg_list[scsiq->next_sg_index],
						 sg_list_dwords);

			scsiq->next_sg_index += ASC_SG_LIST_PER_Q;

			/*
			 * If the just completed SG queue contained the
			 * last SG element, then no more SG queues need
			 * to be written.
			 */
			if (scsi_sg_q.cntl & QCSG_SG_XFER_END) {
				break;
			}

			next_qp = AscReadLramByte(iop_base,
						  (ushort)(q_addr +
							   ASC_SCSIQ_B_FWD));
			q_addr = ASC_QNO_TO_QADDR(next_qp);
		}

		/*
		 * Clear the halt condition so the RISC will be restarted
		 * after the return.
		 */
		AscWriteLramWord(iop_base, ASCV_HALTCODE_W, 0);
		return (0);
	}
#endif /* CC_VERY_LONG_SG_LIST */
	return (0);
}