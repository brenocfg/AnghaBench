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
typedef  int /*<<< orphan*/  wr ;
typedef  union c2wr {int dummy; } c2wr ;
struct TYPE_5__ {scalar_t__ context; } ;
struct c2wr_init_req {void* q2_host_msg_pool; void* q2_host_shared; void* q1_host_msg_pool; void* q1_host_shared; void* q0_host_shared; void* hint_count; TYPE_1__ hdr; } ;
struct TYPE_8__ {int /*<<< orphan*/  host_dma; int /*<<< orphan*/  shared_dma; } ;
struct TYPE_7__ {int /*<<< orphan*/  host_dma; int /*<<< orphan*/  shared_dma; } ;
struct TYPE_6__ {int /*<<< orphan*/  shared_dma; } ;
struct c2_dev {TYPE_4__ aeq; TYPE_3__ rep_vq; TYPE_2__ req_vq; int /*<<< orphan*/  hint_count_dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCWR_INIT ; 
 int /*<<< orphan*/  c2_wr_set_id (struct c2wr_init_req*,int /*<<< orphan*/ ) ; 
 void* cpu_to_be64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct c2wr_init_req*,int /*<<< orphan*/ ,int) ; 
 int vq_send_wr (struct c2_dev*,union c2wr*) ; 

__attribute__((used)) static int c2_adapter_init(struct c2_dev *c2dev)
{
	struct c2wr_init_req wr;
	int err;

	memset(&wr, 0, sizeof(wr));
	c2_wr_set_id(&wr, CCWR_INIT);
	wr.hdr.context = 0;
	wr.hint_count = cpu_to_be64(c2dev->hint_count_dma);
	wr.q0_host_shared = cpu_to_be64(c2dev->req_vq.shared_dma);
	wr.q1_host_shared = cpu_to_be64(c2dev->rep_vq.shared_dma);
	wr.q1_host_msg_pool = cpu_to_be64(c2dev->rep_vq.host_dma);
	wr.q2_host_shared = cpu_to_be64(c2dev->aeq.shared_dma);
	wr.q2_host_msg_pool = cpu_to_be64(c2dev->aeq.host_dma);

	/* Post the init message */
	err = vq_send_wr(c2dev, (union c2wr *) & wr);

	return err;
}