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
struct TYPE_8__ {int pci_out_enabled; int use_enh_siga; } ;
struct TYPE_7__ {TYPE_4__ out; } ;
struct qdio_q {int /*<<< orphan*/  tasklet; TYPE_3__ u; TYPE_2__* irq_ptr; int /*<<< orphan*/  nr_buf_used; } ;
struct TYPE_5__ {int mmwc; } ;
struct TYPE_6__ {TYPE_1__ ssqd_desc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int QDIO_FLAG_PCI_OUT ; 
 scalar_t__ QDIO_IQDIO_QFMT ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 
 unsigned char SLSB_CU_OUTPUT_PRIMED ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fast_requeue ; 
 int /*<<< orphan*/  get_buf_state (struct qdio_q*,int /*<<< orphan*/ ,unsigned char*,int /*<<< orphan*/ ) ; 
 scalar_t__ multicast_outbound (struct qdio_q*) ; 
 scalar_t__ need_siga_sync (struct qdio_q*) ; 
 int next_buf (int) ; 
 int /*<<< orphan*/  outbound_call ; 
 int /*<<< orphan*/  pci_request_int ; 
 int /*<<< orphan*/  prev_buf (int) ; 
 unsigned long qdio_aob_for_buffer (TYPE_4__*,int) ; 
 int qdio_kick_outbound_q (struct qdio_q*,unsigned long) ; 
 int /*<<< orphan*/  qdio_siga_sync_q (struct qdio_q*) ; 
 int /*<<< orphan*/  qperf_inc (struct qdio_q*,int /*<<< orphan*/ ) ; 
 scalar_t__ queue_type (struct qdio_q*) ; 
 int set_buf_states (struct qdio_q*,int,unsigned char,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_outbound(struct qdio_q *q, unsigned int callflags,
			   int bufnr, int count)
{
	unsigned char state;
	int used, rc = 0;

	qperf_inc(q, outbound_call);

	count = set_buf_states(q, bufnr, SLSB_CU_OUTPUT_PRIMED, count);
	used = atomic_add_return(count, &q->nr_buf_used);
	BUG_ON(used > QDIO_MAX_BUFFERS_PER_Q);

	if (callflags & QDIO_FLAG_PCI_OUT) {
		q->u.out.pci_out_enabled = 1;
		qperf_inc(q, pci_request_int);
	}
	else
		q->u.out.pci_out_enabled = 0;

	if (queue_type(q) == QDIO_IQDIO_QFMT) {
		if (multicast_outbound(q))
			rc = qdio_kick_outbound_q(q, 0);
		else
			if ((q->irq_ptr->ssqd_desc.mmwc > 1) &&
			    (count > 1) &&
			    (count <= q->irq_ptr->ssqd_desc.mmwc)) {
				/* exploit enhanced SIGA */
				q->u.out.use_enh_siga = 1;
				rc = qdio_kick_outbound_q(q, 0);
			} else {
				int b2kick;
				unsigned long phys_aob;

				/*
				* One siga-w per buffer required for unicast
				* HiperSockets.
				*/
				q->u.out.use_enh_siga = 0;
				b2kick = bufnr;
				while (count--) {
					phys_aob = qdio_aob_for_buffer(
							&q->u.out, b2kick);
					rc = qdio_kick_outbound_q(q, phys_aob);
					if (rc)
						goto out;
					b2kick = next_buf(b2kick);
				}
			}
		goto out;
	}

	if (need_siga_sync(q)) {
		qdio_siga_sync_q(q);
		goto out;
	}

	/* try to fast requeue buffers */
	get_buf_state(q, prev_buf(bufnr), &state, 0);
	if (state != SLSB_CU_OUTPUT_PRIMED)
		rc = qdio_kick_outbound_q(q, 0);
	else
		qperf_inc(q, fast_requeue);

out:
	tasklet_schedule(&q->tasklet);
	return rc;
}