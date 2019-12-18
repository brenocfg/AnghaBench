#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct lpfc_rcqe {int dummy; } ;
struct lpfc_queue {scalar_t__ queue_id; int /*<<< orphan*/  RQ_no_posted_buf; int /*<<< orphan*/  RQ_rcv_buf; int /*<<< orphan*/  RQ_no_buf_found; int /*<<< orphan*/  RQ_buf_trunc; } ;
struct TYPE_8__ {int /*<<< orphan*/  sp_queue_event; struct lpfc_queue* dat_rq; struct lpfc_queue* hdr_rq; } ;
struct lpfc_hba {int /*<<< orphan*/  hbalock; int /*<<< orphan*/  hba_flag; TYPE_4__ sli4_hba; TYPE_1__* hbqs; } ;
struct TYPE_6__ {int /*<<< orphan*/  rcqe_cmpl; } ;
struct TYPE_7__ {int /*<<< orphan*/  list; TYPE_2__ cqe; } ;
struct hbq_dmabuf {TYPE_3__ cq_event; } ;
struct TYPE_5__ {int /*<<< orphan*/  hbq_buffer_list; } ;

/* Variables and functions */
 scalar_t__ CQE_CODE_RECEIVE_V1 ; 
#define  FC_STATUS_INSUFF_BUF_FRM_DISC 131 
#define  FC_STATUS_INSUFF_BUF_NEED_BUF 130 
#define  FC_STATUS_RQ_BUF_LEN_EXCEEDED 129 
#define  FC_STATUS_RQ_SUCCESS 128 
 int /*<<< orphan*/  HBA_POST_RECEIVE_BUFFER ; 
 int /*<<< orphan*/  HBA_SP_QUEUE_EVT ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_SLI ; 
 scalar_t__ bf_get (int /*<<< orphan*/ ,struct lpfc_rcqe*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_cqe_code ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_rcqe_rq_id ; 
 int /*<<< orphan*/  lpfc_rcqe_rq_id_v1 ; 
 int /*<<< orphan*/  lpfc_rcqe_status ; 
 int /*<<< orphan*/  lpfc_sli4_rq_release (struct lpfc_queue*,struct lpfc_queue*) ; 
 struct hbq_dmabuf* lpfc_sli_hbqbuf_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct lpfc_rcqe*,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
lpfc_sli4_sp_handle_rcqe(struct lpfc_hba *phba, struct lpfc_rcqe *rcqe)
{
	bool workposted = false;
	struct lpfc_queue *hrq = phba->sli4_hba.hdr_rq;
	struct lpfc_queue *drq = phba->sli4_hba.dat_rq;
	struct hbq_dmabuf *dma_buf;
	uint32_t status, rq_id;
	unsigned long iflags;

	/* sanity check on queue memory */
	if (unlikely(!hrq) || unlikely(!drq))
		return workposted;

	if (bf_get(lpfc_cqe_code, rcqe) == CQE_CODE_RECEIVE_V1)
		rq_id = bf_get(lpfc_rcqe_rq_id_v1, rcqe);
	else
		rq_id = bf_get(lpfc_rcqe_rq_id, rcqe);
	if (rq_id != hrq->queue_id)
		goto out;

	status = bf_get(lpfc_rcqe_status, rcqe);
	switch (status) {
	case FC_STATUS_RQ_BUF_LEN_EXCEEDED:
		lpfc_printf_log(phba, KERN_ERR, LOG_SLI,
				"2537 Receive Frame Truncated!!\n");
		hrq->RQ_buf_trunc++;
	case FC_STATUS_RQ_SUCCESS:
		lpfc_sli4_rq_release(hrq, drq);
		spin_lock_irqsave(&phba->hbalock, iflags);
		dma_buf = lpfc_sli_hbqbuf_get(&phba->hbqs[0].hbq_buffer_list);
		if (!dma_buf) {
			hrq->RQ_no_buf_found++;
			spin_unlock_irqrestore(&phba->hbalock, iflags);
			goto out;
		}
		hrq->RQ_rcv_buf++;
		memcpy(&dma_buf->cq_event.cqe.rcqe_cmpl, rcqe, sizeof(*rcqe));
		/* save off the frame for the word thread to process */
		list_add_tail(&dma_buf->cq_event.list,
			      &phba->sli4_hba.sp_queue_event);
		/* Frame received */
		phba->hba_flag |= HBA_SP_QUEUE_EVT;
		spin_unlock_irqrestore(&phba->hbalock, iflags);
		workposted = true;
		break;
	case FC_STATUS_INSUFF_BUF_NEED_BUF:
	case FC_STATUS_INSUFF_BUF_FRM_DISC:
		hrq->RQ_no_posted_buf++;
		/* Post more buffers if possible */
		spin_lock_irqsave(&phba->hbalock, iflags);
		phba->hba_flag |= HBA_POST_RECEIVE_BUFFER;
		spin_unlock_irqrestore(&phba->hbalock, iflags);
		workposted = true;
		break;
	}
out:
	return workposted;
}