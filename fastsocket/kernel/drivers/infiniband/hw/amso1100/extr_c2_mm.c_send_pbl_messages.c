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
typedef  union c2wr {int dummy; } c2wr ;
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_4__ {unsigned long context; } ;
struct c2wr_nsmr_pbl_req {int /*<<< orphan*/ * paddrs; TYPE_2__ hdr; void* flags; void* addrs_length; int /*<<< orphan*/  stag_index; int /*<<< orphan*/  rnic_handle; } ;
struct c2wr_nsmr_pbl_rep {int dummy; } ;
struct c2_vq_req {scalar_t__ reply_msg; } ;
struct TYPE_3__ {int msg_size; } ;
struct c2_dev {int /*<<< orphan*/  adapter_handle; TYPE_1__ req_vq; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  CCWR_NSMR_PBL ; 
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int MEM_PBL_COMPLETE ; 
 scalar_t__ PAGE_SIZE ; 
#define  PBL_PHYS 129 
#define  PBL_VIRT 128 
 int c2_errno (struct c2wr_nsmr_pbl_rep*) ; 
 int /*<<< orphan*/  c2_wr_set_id (struct c2wr_nsmr_pbl_req*,int /*<<< orphan*/ ) ; 
 void* cpu_to_be32 (int) ; 
 int /*<<< orphan*/  cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct c2wr_nsmr_pbl_req*) ; 
 struct c2wr_nsmr_pbl_req* kmalloc (int,int /*<<< orphan*/ ) ; 
 int min (int,int) ; 
 int /*<<< orphan*/  vq_repbuf_free (struct c2_dev*,struct c2wr_nsmr_pbl_rep*) ; 
 int /*<<< orphan*/  vq_req_get (struct c2_dev*,struct c2_vq_req*) ; 
 int /*<<< orphan*/  vq_req_put (struct c2_dev*,struct c2_vq_req*) ; 
 int vq_send_wr (struct c2_dev*,union c2wr*) ; 
 int vq_wait_for_reply (struct c2_dev*,struct c2_vq_req*) ; 

__attribute__((used)) static int
send_pbl_messages(struct c2_dev *c2dev, __be32 stag_index,
		  unsigned long va, u32 pbl_depth,
		  struct c2_vq_req *vq_req, int pbl_type)
{
	u32 pbe_count;		/* amt that fits in a PBL msg */
	u32 count;		/* amt in this PBL MSG. */
	struct c2wr_nsmr_pbl_req *wr;	/* PBL WR ptr */
	struct c2wr_nsmr_pbl_rep *reply;	/* reply ptr */
 	int err, pbl_virt, pbl_index, i;

	switch (pbl_type) {
	case PBL_VIRT:
		pbl_virt = 1;
		break;
	case PBL_PHYS:
		pbl_virt = 0;
		break;
	default:
		return -EINVAL;
		break;
	}

	pbe_count = (c2dev->req_vq.msg_size -
		     sizeof(struct c2wr_nsmr_pbl_req)) / sizeof(u64);
	wr = kmalloc(c2dev->req_vq.msg_size, GFP_KERNEL);
	if (!wr) {
		return -ENOMEM;
	}
	c2_wr_set_id(wr, CCWR_NSMR_PBL);

	/*
	 * Only the last PBL message will generate a reply from the verbs,
	 * so we set the context to 0 indicating there is no kernel verbs
	 * handler blocked awaiting this reply.
	 */
	wr->hdr.context = 0;
	wr->rnic_handle = c2dev->adapter_handle;
	wr->stag_index = stag_index;	/* already swapped */
	wr->flags = 0;
	pbl_index = 0;
	while (pbl_depth) {
		count = min(pbe_count, pbl_depth);
		wr->addrs_length = cpu_to_be32(count);

		/*
		 *  If this is the last message, then reference the
		 *  vq request struct cuz we're gonna wait for a reply.
		 *  also make this PBL msg as the last one.
		 */
		if (count == pbl_depth) {
			/*
			 * reference the request struct.  dereferenced in the
			 * int handler.
			 */
			vq_req_get(c2dev, vq_req);
			wr->flags = cpu_to_be32(MEM_PBL_COMPLETE);

			/*
			 * This is the last PBL message.
			 * Set the context to our VQ Request Object so we can
			 * wait for the reply.
			 */
			wr->hdr.context = (unsigned long) vq_req;
		}

		/*
		 * If pbl_virt is set then va is a virtual address
		 * that describes a virtually contiguous memory
		 * allocation. The wr needs the start of each virtual page
		 * to be converted to the corresponding physical address
		 * of the page. If pbl_virt is not set then va is an array
		 * of physical addresses and there is no conversion to do.
		 * Just fill in the wr with what is in the array.
		 */
		for (i = 0; i < count; i++) {
			if (pbl_virt) {
				va += PAGE_SIZE;
			} else {
 				wr->paddrs[i] =
				    cpu_to_be64(((u64 *)va)[pbl_index + i]);
			}
		}

		/*
		 * Send WR to adapter
		 */
		err = vq_send_wr(c2dev, (union c2wr *) wr);
		if (err) {
			if (count <= pbe_count) {
				vq_req_put(c2dev, vq_req);
			}
			goto bail0;
		}
		pbl_depth -= count;
		pbl_index += count;
	}

	/*
	 *  Now wait for the reply...
	 */
	err = vq_wait_for_reply(c2dev, vq_req);
	if (err) {
		goto bail0;
	}

	/*
	 * Process reply
	 */
	reply = (struct c2wr_nsmr_pbl_rep *) (unsigned long) vq_req->reply_msg;
	if (!reply) {
		err = -ENOMEM;
		goto bail0;
	}

	err = c2_errno(reply);

	vq_repbuf_free(c2dev, reply);
      bail0:
	kfree(wr);
	return err;
}