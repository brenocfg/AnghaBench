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
typedef  union c2wr {int dummy; } c2wr ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
typedef  int u16 ;
struct TYPE_5__ {unsigned long context; } ;
struct c2wr_nsmr_register_req {void** paddrs; void* addrs_length; void* fbo; void* pbl_depth; void* length; void* pbe_size; int /*<<< orphan*/  pd_id; void* va; scalar_t__ stag_key; int /*<<< orphan*/  flags; int /*<<< orphan*/  rnic_handle; TYPE_1__ hdr; } ;
struct c2wr_nsmr_register_rep {int /*<<< orphan*/  stag_index; } ;
struct c2_vq_req {unsigned long reply_msg; int /*<<< orphan*/  reply_ready; } ;
struct TYPE_8__ {int lkey; int rkey; } ;
struct c2_mr {TYPE_4__ ibmr; TYPE_3__* pd; } ;
struct TYPE_6__ {int msg_size; } ;
struct c2_dev {TYPE_2__ req_vq; int /*<<< orphan*/  adapter_handle; } ;
typedef  enum c2_acf { ____Placeholder_c2_acf } c2_acf ;
struct TYPE_7__ {int /*<<< orphan*/  pd_id; } ;

/* Variables and functions */
 int C2_PBL_MAX_DEPTH ; 
 int /*<<< orphan*/  CCWR_NSMR_REGISTER ; 
 int EINTR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MEM_PBL_COMPLETE ; 
 int MEM_REMOTE ; 
 int MEM_VA_BASED ; 
 int /*<<< orphan*/  PBL_PHYS ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int c2_errno (struct c2wr_nsmr_register_rep*) ; 
 int /*<<< orphan*/  c2_wr_set_id (struct c2wr_nsmr_register_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be16 (int) ; 
 void* cpu_to_be32 (int) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct c2wr_nsmr_register_req*) ; 
 struct c2wr_nsmr_register_req* kmalloc (int,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int send_pbl_messages (struct c2_dev*,void*,unsigned long,int,struct c2_vq_req*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vq_repbuf_free (struct c2_dev*,struct c2wr_nsmr_register_rep*) ; 
 struct c2_vq_req* vq_req_alloc (struct c2_dev*) ; 
 int /*<<< orphan*/  vq_req_free (struct c2_dev*,struct c2_vq_req*) ; 
 int /*<<< orphan*/  vq_req_get (struct c2_dev*,struct c2_vq_req*) ; 
 int /*<<< orphan*/  vq_req_put (struct c2_dev*,struct c2_vq_req*) ; 
 int vq_send_wr (struct c2_dev*,union c2wr*) ; 
 int vq_wait_for_reply (struct c2_dev*,struct c2_vq_req*) ; 

int
c2_nsmr_register_phys_kern(struct c2_dev *c2dev, u64 *addr_list,
 			   int page_size, int pbl_depth, u32 length,
 			   u32 offset, u64 *va, enum c2_acf acf,
			   struct c2_mr *mr)
{
	struct c2_vq_req *vq_req;
	struct c2wr_nsmr_register_req *wr;
	struct c2wr_nsmr_register_rep *reply;
	u16 flags;
	int i, pbe_count, count;
	int err;

	if (!va || !length || !addr_list || !pbl_depth)
		return -EINTR;

	/*
	 * Verify PBL depth is within rnic max
	 */
	if (pbl_depth > C2_PBL_MAX_DEPTH) {
		return -EINTR;
	}

	/*
	 * allocate verbs request object
	 */
	vq_req = vq_req_alloc(c2dev);
	if (!vq_req)
		return -ENOMEM;

	wr = kmalloc(c2dev->req_vq.msg_size, GFP_KERNEL);
	if (!wr) {
		err = -ENOMEM;
		goto bail0;
	}

	/*
	 * build the WR
	 */
	c2_wr_set_id(wr, CCWR_NSMR_REGISTER);
	wr->hdr.context = (unsigned long) vq_req;
	wr->rnic_handle = c2dev->adapter_handle;

	flags = (acf | MEM_VA_BASED | MEM_REMOTE);

	/*
	 * compute how many pbes can fit in the message
	 */
	pbe_count = (c2dev->req_vq.msg_size -
		     sizeof(struct c2wr_nsmr_register_req)) / sizeof(u64);

	if (pbl_depth <= pbe_count) {
		flags |= MEM_PBL_COMPLETE;
	}
	wr->flags = cpu_to_be16(flags);
	wr->stag_key = 0;	//stag_key;
	wr->va = cpu_to_be64(*va);
	wr->pd_id = mr->pd->pd_id;
	wr->pbe_size = cpu_to_be32(page_size);
	wr->length = cpu_to_be32(length);
	wr->pbl_depth = cpu_to_be32(pbl_depth);
	wr->fbo = cpu_to_be32(offset);
	count = min(pbl_depth, pbe_count);
	wr->addrs_length = cpu_to_be32(count);

	/*
	 * fill out the PBL for this message
	 */
	for (i = 0; i < count; i++) {
		wr->paddrs[i] = cpu_to_be64(addr_list[i]);
	}

	/*
	 * regerence the request struct
	 */
	vq_req_get(c2dev, vq_req);

	/*
	 * send the WR to the adapter
	 */
	err = vq_send_wr(c2dev, (union c2wr *) wr);
	if (err) {
		vq_req_put(c2dev, vq_req);
		goto bail1;
	}

	/*
	 * wait for reply from adapter
	 */
	err = vq_wait_for_reply(c2dev, vq_req);
	if (err) {
		goto bail1;
	}

	/*
	 * process reply
	 */
	reply =
	    (struct c2wr_nsmr_register_rep *) (unsigned long) (vq_req->reply_msg);
	if (!reply) {
		err = -ENOMEM;
		goto bail1;
	}
	if ((err = c2_errno(reply))) {
		goto bail2;
	}
	//*p_pb_entries = be32_to_cpu(reply->pbl_depth);
	mr->ibmr.lkey = mr->ibmr.rkey = be32_to_cpu(reply->stag_index);
	vq_repbuf_free(c2dev, reply);

	/*
	 * if there are still more PBEs we need to send them to
	 * the adapter and wait for a reply on the final one.
	 * reuse vq_req for this purpose.
	 */
	pbl_depth -= count;
	if (pbl_depth) {

		vq_req->reply_msg = (unsigned long) NULL;
		atomic_set(&vq_req->reply_ready, 0);
		err = send_pbl_messages(c2dev,
					cpu_to_be32(mr->ibmr.lkey),
					(unsigned long) &addr_list[i],
					pbl_depth, vq_req, PBL_PHYS);
		if (err) {
			goto bail1;
		}
	}

	vq_req_free(c2dev, vq_req);
	kfree(wr);

	return err;

      bail2:
	vq_repbuf_free(c2dev, reply);
      bail1:
	kfree(wr);
      bail0:
	vq_req_free(c2dev, vq_req);
	return err;
}