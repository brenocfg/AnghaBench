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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct carm_request {unsigned int tag; int /*<<< orphan*/  rq; scalar_t__ msg_bucket; void* msg_subtype; void* msg_type; } ;
struct carm_msg_ioctl {void* data_addr; void* handle; scalar_t__ array_id; void* subtype; void* type; } ;
struct carm_host {scalar_t__ state; int /*<<< orphan*/  lock; int /*<<< orphan*/  oob_q; } ;
struct carm_array_info {int dummy; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 void* CARM_ARRAY_INFO ; 
 void* CARM_MSG_ARRAY ; 
 int /*<<< orphan*/  DPRINTK (char*,unsigned int) ; 
 int ENOMEM ; 
 scalar_t__ HST_DEV_SCAN ; 
 scalar_t__ HST_DEV_SCAN_START ; 
 scalar_t__ HST_ERROR ; 
 scalar_t__ TAG_ENCODE (unsigned int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  blk_insert_request (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct carm_request*) ; 
 struct carm_request* carm_get_special (struct carm_host*) ; 
 int carm_lookup_bucket (int) ; 
 struct carm_msg_ioctl* carm_ref_msg (struct carm_host*,unsigned int) ; 
 scalar_t__ carm_ref_msg_dma (struct carm_host*,unsigned int) ; 
 void* cpu_to_le32 (scalar_t__) ; 
 int /*<<< orphan*/  memset (struct carm_msg_ioctl*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int carm_array_info (struct carm_host *host, unsigned int array_idx)
{
	struct carm_msg_ioctl *ioc;
	unsigned int idx;
	u32 msg_data;
	dma_addr_t msg_dma;
	struct carm_request *crq;
	int rc;

	crq = carm_get_special(host);
	if (!crq) {
		rc = -ENOMEM;
		goto err_out;
	}

	idx = crq->tag;

	ioc = carm_ref_msg(host, idx);
	msg_dma = carm_ref_msg_dma(host, idx);
	msg_data = (u32) (msg_dma + sizeof(struct carm_array_info));

	crq->msg_type = CARM_MSG_ARRAY;
	crq->msg_subtype = CARM_ARRAY_INFO;
	rc = carm_lookup_bucket(sizeof(struct carm_msg_ioctl) +
				sizeof(struct carm_array_info));
	BUG_ON(rc < 0);
	crq->msg_bucket = (u32) rc;

	memset(ioc, 0, sizeof(*ioc));
	ioc->type	= CARM_MSG_ARRAY;
	ioc->subtype	= CARM_ARRAY_INFO;
	ioc->array_id	= (u8) array_idx;
	ioc->handle	= cpu_to_le32(TAG_ENCODE(idx));
	ioc->data_addr	= cpu_to_le32(msg_data);

	spin_lock_irq(&host->lock);
	assert(host->state == HST_DEV_SCAN_START ||
	       host->state == HST_DEV_SCAN);
	spin_unlock_irq(&host->lock);

	DPRINTK("blk_insert_request, tag == %u\n", idx);
	blk_insert_request(host->oob_q, crq->rq, 1, crq);

	return 0;

err_out:
	spin_lock_irq(&host->lock);
	host->state = HST_ERROR;
	spin_unlock_irq(&host->lock);
	return rc;
}