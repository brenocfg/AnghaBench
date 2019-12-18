#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ushort ;
typedef  void* uchar ;
struct TYPE_16__ {int /*<<< orphan*/  iop_base; } ;
struct TYPE_12__ {int sg_queue_cnt; void* data_cnt; void* data_addr; int /*<<< orphan*/  cntl; } ;
struct TYPE_15__ {int next_sg_index; TYPE_2__ q1; scalar_t__ remain_sg_entry_cnt; TYPE_4__* sg_head; } ;
struct TYPE_14__ {scalar_t__ entry_cnt; int queue_cnt; TYPE_1__* sg_list; } ;
struct TYPE_13__ {int seq_no; int sg_list_cnt; int sg_cur_list_cnt; void* q_no; int /*<<< orphan*/  cntl; void* sg_head_qp; } ;
struct TYPE_11__ {scalar_t__ bytes; scalar_t__ addr; } ;
typedef  int /*<<< orphan*/  PortAddr ;
typedef  TYPE_3__ ASC_SG_LIST_Q ;
typedef  TYPE_4__ ASC_SG_HEAD ;
typedef  TYPE_5__ ASC_SCSI_Q ;
typedef  void* ASC_PADDR ;
typedef  TYPE_6__ ASC_DVC_VAR ;
typedef  void* ASC_DCNT ;

/* Variables and functions */
 scalar_t__ ASC_MAX_SG_LIST ; 
 int ASC_QNO_TO_QADDR (void*) ; 
 int ASC_SCSIQ_B_FWD ; 
 int ASC_SCSIQ_SGHD_CPY_BEG ; 
 int ASC_SGQ_LIST_BEG ; 
 int ASC_SG_LIST_PER_Q ; 
 int /*<<< orphan*/  AscMemDWordCopyPtrToLram (int /*<<< orphan*/ ,int,void**,int) ; 
 int /*<<< orphan*/  AscMemWordCopyPtrToLram (int /*<<< orphan*/ ,int,void**,int) ; 
 int AscPutReadyQueue (TYPE_6__*,TYPE_5__*,void*) ; 
 void* AscReadLramByte (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  QCSG_SG_XFER_END ; 
 int /*<<< orphan*/  QCSG_SG_XFER_LIST ; 
 int /*<<< orphan*/  QCSG_SG_XFER_MORE ; 
 int /*<<< orphan*/  QC_SG_HEAD ; 

__attribute__((used)) static int
AscPutReadySgListQueue(ASC_DVC_VAR *asc_dvc, ASC_SCSI_Q *scsiq, uchar q_no)
{
	int sta;
	int i;
	ASC_SG_HEAD *sg_head;
	ASC_SG_LIST_Q scsi_sg_q;
	ASC_DCNT saved_data_addr;
	ASC_DCNT saved_data_cnt;
	PortAddr iop_base;
	ushort sg_list_dwords;
	ushort sg_index;
	ushort sg_entry_cnt;
	ushort q_addr;
	uchar next_qp;

	iop_base = asc_dvc->iop_base;
	sg_head = scsiq->sg_head;
	saved_data_addr = scsiq->q1.data_addr;
	saved_data_cnt = scsiq->q1.data_cnt;
	scsiq->q1.data_addr = (ASC_PADDR) sg_head->sg_list[0].addr;
	scsiq->q1.data_cnt = (ASC_DCNT) sg_head->sg_list[0].bytes;
#if CC_VERY_LONG_SG_LIST
	/*
	 * If sg_head->entry_cnt is greater than ASC_MAX_SG_LIST
	 * then not all SG elements will fit in the allocated queues.
	 * The rest of the SG elements will be copied when the RISC
	 * completes the SG elements that fit and halts.
	 */
	if (sg_head->entry_cnt > ASC_MAX_SG_LIST) {
		/*
		 * Set sg_entry_cnt to be the number of SG elements that
		 * will fit in the allocated SG queues. It is minus 1, because
		 * the first SG element is handled above. ASC_MAX_SG_LIST is
		 * already inflated by 1 to account for this. For example it
		 * may be 50 which is 1 + 7 queues * 7 SG elements.
		 */
		sg_entry_cnt = ASC_MAX_SG_LIST - 1;

		/*
		 * Keep track of remaining number of SG elements that will
		 * need to be handled from a_isr.c.
		 */
		scsiq->remain_sg_entry_cnt =
		    sg_head->entry_cnt - ASC_MAX_SG_LIST;
	} else {
#endif /* CC_VERY_LONG_SG_LIST */
		/*
		 * Set sg_entry_cnt to be the number of SG elements that
		 * will fit in the allocated SG queues. It is minus 1, because
		 * the first SG element is handled above.
		 */
		sg_entry_cnt = sg_head->entry_cnt - 1;
#if CC_VERY_LONG_SG_LIST
	}
#endif /* CC_VERY_LONG_SG_LIST */
	if (sg_entry_cnt != 0) {
		scsiq->q1.cntl |= QC_SG_HEAD;
		q_addr = ASC_QNO_TO_QADDR(q_no);
		sg_index = 1;
		scsiq->q1.sg_queue_cnt = sg_head->queue_cnt;
		scsi_sg_q.sg_head_qp = q_no;
		scsi_sg_q.cntl = QCSG_SG_XFER_LIST;
		for (i = 0; i < sg_head->queue_cnt; i++) {
			scsi_sg_q.seq_no = i + 1;
			if (sg_entry_cnt > ASC_SG_LIST_PER_Q) {
				sg_list_dwords = (uchar)(ASC_SG_LIST_PER_Q * 2);
				sg_entry_cnt -= ASC_SG_LIST_PER_Q;
				if (i == 0) {
					scsi_sg_q.sg_list_cnt =
					    ASC_SG_LIST_PER_Q;
					scsi_sg_q.sg_cur_list_cnt =
					    ASC_SG_LIST_PER_Q;
				} else {
					scsi_sg_q.sg_list_cnt =
					    ASC_SG_LIST_PER_Q - 1;
					scsi_sg_q.sg_cur_list_cnt =
					    ASC_SG_LIST_PER_Q - 1;
				}
			} else {
#if CC_VERY_LONG_SG_LIST
				/*
				 * This is the last SG queue in the list of
				 * allocated SG queues. If there are more
				 * SG elements than will fit in the allocated
				 * queues, then set the QCSG_SG_XFER_MORE flag.
				 */
				if (sg_head->entry_cnt > ASC_MAX_SG_LIST) {
					scsi_sg_q.cntl |= QCSG_SG_XFER_MORE;
				} else {
#endif /* CC_VERY_LONG_SG_LIST */
					scsi_sg_q.cntl |= QCSG_SG_XFER_END;
#if CC_VERY_LONG_SG_LIST
				}
#endif /* CC_VERY_LONG_SG_LIST */
				sg_list_dwords = sg_entry_cnt << 1;
				if (i == 0) {
					scsi_sg_q.sg_list_cnt = sg_entry_cnt;
					scsi_sg_q.sg_cur_list_cnt =
					    sg_entry_cnt;
				} else {
					scsi_sg_q.sg_list_cnt =
					    sg_entry_cnt - 1;
					scsi_sg_q.sg_cur_list_cnt =
					    sg_entry_cnt - 1;
				}
				sg_entry_cnt = 0;
			}
			next_qp = AscReadLramByte(iop_base,
						  (ushort)(q_addr +
							   ASC_SCSIQ_B_FWD));
			scsi_sg_q.q_no = next_qp;
			q_addr = ASC_QNO_TO_QADDR(next_qp);
			AscMemWordCopyPtrToLram(iop_base,
						q_addr + ASC_SCSIQ_SGHD_CPY_BEG,
						(uchar *)&scsi_sg_q,
						sizeof(ASC_SG_LIST_Q) >> 1);
			AscMemDWordCopyPtrToLram(iop_base,
						 q_addr + ASC_SGQ_LIST_BEG,
						 (uchar *)&sg_head->
						 sg_list[sg_index],
						 sg_list_dwords);
			sg_index += ASC_SG_LIST_PER_Q;
			scsiq->next_sg_index = sg_index;
		}
	} else {
		scsiq->q1.cntl &= ~QC_SG_HEAD;
	}
	sta = AscPutReadyQueue(asc_dvc, scsiq, q_no);
	scsiq->q1.data_addr = saved_data_addr;
	scsiq->q1.data_cnt = saved_data_cnt;
	return (sta);
}