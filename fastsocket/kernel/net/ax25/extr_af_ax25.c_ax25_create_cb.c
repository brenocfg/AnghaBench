#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  state; int /*<<< orphan*/  reseq_queue; int /*<<< orphan*/  ack_queue; int /*<<< orphan*/  frag_queue; int /*<<< orphan*/  write_queue; int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ ax25_cb ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_STATE_0 ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ax25_fillin_cb (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ax25_setup_timers (TYPE_1__*) ; 
 TYPE_1__* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 

ax25_cb *ax25_create_cb(void)
{
	ax25_cb *ax25;

	if ((ax25 = kzalloc(sizeof(*ax25), GFP_ATOMIC)) == NULL)
		return NULL;

	atomic_set(&ax25->refcount, 1);

	skb_queue_head_init(&ax25->write_queue);
	skb_queue_head_init(&ax25->frag_queue);
	skb_queue_head_init(&ax25->ack_queue);
	skb_queue_head_init(&ax25->reseq_queue);

	ax25_setup_timers(ax25);

	ax25_fillin_cb(ax25, NULL);

	ax25->state = AX25_STATE_0;

	return ax25;
}