#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct qeth_qdio_q {int dummy; } ;
struct TYPE_12__ {int no_in_queues; int no_out_queues; TYPE_6__* c_q; TYPE_3__** out_qs; struct qdio_outbuf_state* out_bufstates; } ;
struct TYPE_9__ {scalar_t__ cq; } ;
struct qeth_card {TYPE_5__* gdev; TYPE_4__ qdio; TYPE_1__ options; } ;
struct qdio_outbuf_state {int dummy; } ;
struct TYPE_14__ {int /*<<< orphan*/ * qdio_bufs; TYPE_2__* bufs; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;
struct TYPE_11__ {struct qdio_outbuf_state* bufstates; } ;
struct TYPE_10__ {int /*<<< orphan*/ * buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int QDIO_MAX_BUFFERS_PER_Q ; 
 scalar_t__ QETH_CQ_ENABLED ; 
 int /*<<< orphan*/  QETH_DBF_HEX (int /*<<< orphan*/ ,int,TYPE_6__**,int) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  QETH_DBF_TEXT_ (int /*<<< orphan*/ ,int,char*,int) ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (TYPE_6__*) ; 
 TYPE_6__* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int qeth_alloc_cq(struct qeth_card *card)
{
	int rc;

	if (card->options.cq == QETH_CQ_ENABLED) {
		int i;
		struct qdio_outbuf_state *outbuf_states;

		QETH_DBF_TEXT(SETUP, 2, "cqon");
		card->qdio.c_q = kzalloc(sizeof(struct qeth_qdio_q),
					 GFP_KERNEL);
		if (!card->qdio.c_q) {
			rc = -1;
			goto kmsg_out;
		}
		QETH_DBF_HEX(SETUP, 2, &card->qdio.c_q, sizeof(void *));

		for (i = 0; i < QDIO_MAX_BUFFERS_PER_Q; ++i) {
			card->qdio.c_q->bufs[i].buffer =
				&card->qdio.c_q->qdio_bufs[i];
		}

		card->qdio.no_in_queues = 2;

		card->qdio.out_bufstates = (struct qdio_outbuf_state *)
			kzalloc(card->qdio.no_out_queues *
				QDIO_MAX_BUFFERS_PER_Q *
				sizeof(struct qdio_outbuf_state), GFP_KERNEL);
		outbuf_states = card->qdio.out_bufstates;
		if (outbuf_states == NULL) {
			rc = -1;
			goto free_cq_out;
		}
		for (i = 0; i < card->qdio.no_out_queues; ++i) {
			card->qdio.out_qs[i]->bufstates = outbuf_states;
			outbuf_states += QDIO_MAX_BUFFERS_PER_Q;
		}
	} else {
		QETH_DBF_TEXT(SETUP, 2, "nocq");
		card->qdio.c_q = NULL;
		card->qdio.no_in_queues = 1;
	}
	QETH_DBF_TEXT_(SETUP, 2, "iqc%d", card->qdio.no_in_queues);
	rc = 0;
out:
	return rc;
free_cq_out:
	kfree(card->qdio.c_q);
	card->qdio.c_q = NULL;
kmsg_out:
	dev_err(&card->gdev->dev, "Failed to create completion queue\n");
	goto out;
}