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
typedef  size_t u8 ;
struct veth_msg {int token; } ;
struct TYPE_3__ {int num_buffers; int ack_timeout; int /*<<< orphan*/  ack_threshold; } ;
struct TYPE_4__ {unsigned long data; int /*<<< orphan*/  function; } ;
struct veth_lpar_connection {size_t remote_lp; int reset_timeout; int num_events; TYPE_1__ local_caps; struct veth_msg* msgs; int /*<<< orphan*/  kobject; int /*<<< orphan*/  pending_acks; TYPE_2__ reset_timer; TYPE_2__ ack_timer; int /*<<< orphan*/  statemachine_wq; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACK_THRESHOLD ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int HZ ; 
 int /*<<< orphan*/  HvLpConfig_doLpsCommunicateOnVirtualLan (size_t,size_t) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int VETH_ACKTIMEOUT ; 
 int VETH_NUMBUFFERS ; 
 int /*<<< orphan*/  init_timer (TYPE_2__*) ; 
 struct veth_msg* kcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct veth_lpar_connection* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 size_t this_lp ; 
 int veth_allocate_events (size_t,int) ; 
 struct veth_lpar_connection** veth_cnx ; 
 int /*<<< orphan*/  veth_error (char*,size_t) ; 
 int /*<<< orphan*/  veth_lpar_connection_ktype ; 
 int /*<<< orphan*/  veth_stack_push (struct veth_lpar_connection*,struct veth_msg*) ; 
 int /*<<< orphan*/  veth_statemachine ; 
 int /*<<< orphan*/  veth_timed_ack ; 
 int /*<<< orphan*/  veth_timed_reset ; 

__attribute__((used)) static int veth_init_connection(u8 rlp)
{
	struct veth_lpar_connection *cnx;
	struct veth_msg *msgs;
	int i;

	if ( (rlp == this_lp)
	     || ! HvLpConfig_doLpsCommunicateOnVirtualLan(this_lp, rlp) )
		return 0;

	cnx = kzalloc(sizeof(*cnx), GFP_KERNEL);
	if (! cnx)
		return -ENOMEM;

	cnx->remote_lp = rlp;
	spin_lock_init(&cnx->lock);
	INIT_DELAYED_WORK(&cnx->statemachine_wq, veth_statemachine);

	init_timer(&cnx->ack_timer);
	cnx->ack_timer.function = veth_timed_ack;
	cnx->ack_timer.data = (unsigned long) cnx;

	init_timer(&cnx->reset_timer);
	cnx->reset_timer.function = veth_timed_reset;
	cnx->reset_timer.data = (unsigned long) cnx;
	cnx->reset_timeout = 5 * HZ * (VETH_ACKTIMEOUT / 1000000);

	memset(&cnx->pending_acks, 0xff, sizeof (cnx->pending_acks));

	veth_cnx[rlp] = cnx;

	/* This gets us 1 reference, which is held on behalf of the driver
	 * infrastructure. It's released at module unload. */
	kobject_init(&cnx->kobject, &veth_lpar_connection_ktype);

	msgs = kcalloc(VETH_NUMBUFFERS, sizeof(struct veth_msg), GFP_KERNEL);
	if (! msgs) {
		veth_error("Can't allocate buffers for LPAR %d.\n", rlp);
		return -ENOMEM;
	}

	cnx->msgs = msgs;

	for (i = 0; i < VETH_NUMBUFFERS; i++) {
		msgs[i].token = i;
		veth_stack_push(cnx, msgs + i);
	}

	cnx->num_events = veth_allocate_events(rlp, 2 + VETH_NUMBUFFERS);

	if (cnx->num_events < (2 + VETH_NUMBUFFERS)) {
		veth_error("Can't allocate enough events for LPAR %d.\n", rlp);
		return -ENOMEM;
	}

	cnx->local_caps.num_buffers = VETH_NUMBUFFERS;
	cnx->local_caps.ack_threshold = ACK_THRESHOLD;
	cnx->local_caps.ack_timeout = VETH_ACKTIMEOUT;

	return 0;
}