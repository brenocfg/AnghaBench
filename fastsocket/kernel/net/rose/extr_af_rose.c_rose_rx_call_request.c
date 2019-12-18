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
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  sk_receive_queue; int /*<<< orphan*/  sk_ack_backlog; int /*<<< orphan*/  sk_state; } ;
struct sk_buff {int* data; int /*<<< orphan*/  len; struct sock* sk; } ;
struct rose_facilities_struct {int dest_ndigis; int source_ndigis; int /*<<< orphan*/ * source_digis; int /*<<< orphan*/  source_call; int /*<<< orphan*/  source_addr; int /*<<< orphan*/ * dest_digis; int /*<<< orphan*/  dest_call; int /*<<< orphan*/  dest_addr; } ;
struct rose_sock {unsigned int lci; int dest_ndigis; int source_ndigis; int condition; scalar_t__ vl; scalar_t__ vr; scalar_t__ va; scalar_t__ vs; int /*<<< orphan*/  state; scalar_t__ defer; struct rose_neigh* neighbour; struct rose_facilities_struct facilities; struct net_device* device; int /*<<< orphan*/ * source_digis; int /*<<< orphan*/  source_call; int /*<<< orphan*/  source_addr; int /*<<< orphan*/ * dest_digis; int /*<<< orphan*/  dest_call; int /*<<< orphan*/  dest_addr; } ;
struct rose_neigh {int /*<<< orphan*/  use; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ROSE_CALL_ACCEPTED ; 
 int /*<<< orphan*/  ROSE_INVALID_FACILITY ; 
 int /*<<< orphan*/  ROSE_NETWORK_CONGESTION ; 
 int /*<<< orphan*/  ROSE_STATE_3 ; 
 int /*<<< orphan*/  ROSE_STATE_5 ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  TCP_ESTABLISHED ; 
 int /*<<< orphan*/  memset (struct rose_facilities_struct*,int,int) ; 
 struct sock* rose_find_listener (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rose_insert_socket (struct sock*) ; 
 struct sock* rose_make_new (struct sock*) ; 
 int /*<<< orphan*/  rose_parse_facilities (int*,struct rose_facilities_struct*) ; 
 struct rose_sock* rose_sk (struct sock*) ; 
 int /*<<< orphan*/  rose_start_heartbeat (struct sock*) ; 
 int /*<<< orphan*/  rose_start_idletimer (struct sock*) ; 
 int /*<<< orphan*/  rose_transmit_clear_request (struct rose_neigh*,unsigned int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rose_write_internal (struct sock*,int /*<<< orphan*/ ) ; 
 scalar_t__ sk_acceptq_is_full (struct sock*) ; 
 int /*<<< orphan*/  skb_queue_head (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int /*<<< orphan*/ ) ; 

int rose_rx_call_request(struct sk_buff *skb, struct net_device *dev, struct rose_neigh *neigh, unsigned int lci)
{
	struct sock *sk;
	struct sock *make;
	struct rose_sock *make_rose;
	struct rose_facilities_struct facilities;
	int n, len;

	skb->sk = NULL;		/* Initially we don't know who it's for */

	/*
	 *	skb->data points to the rose frame start
	 */
	memset(&facilities, 0x00, sizeof(struct rose_facilities_struct));

	len  = (((skb->data[3] >> 4) & 0x0F) + 1) >> 1;
	len += (((skb->data[3] >> 0) & 0x0F) + 1) >> 1;
	if (!rose_parse_facilities(skb->data + len + 4, &facilities)) {
		rose_transmit_clear_request(neigh, lci, ROSE_INVALID_FACILITY, 76);
		return 0;
	}

	sk = rose_find_listener(&facilities.source_addr, &facilities.source_call);

	/*
	 * We can't accept the Call Request.
	 */
	if (sk == NULL || sk_acceptq_is_full(sk) ||
	    (make = rose_make_new(sk)) == NULL) {
		rose_transmit_clear_request(neigh, lci, ROSE_NETWORK_CONGESTION, 120);
		return 0;
	}

	skb->sk     = make;
	make->sk_state = TCP_ESTABLISHED;
	make_rose = rose_sk(make);

	make_rose->lci           = lci;
	make_rose->dest_addr     = facilities.dest_addr;
	make_rose->dest_call     = facilities.dest_call;
	make_rose->dest_ndigis   = facilities.dest_ndigis;
	for (n = 0 ; n < facilities.dest_ndigis ; n++)
		make_rose->dest_digis[n] = facilities.dest_digis[n];
	make_rose->source_addr   = facilities.source_addr;
	make_rose->source_call   = facilities.source_call;
	make_rose->source_ndigis = facilities.source_ndigis;
	for (n = 0 ; n < facilities.source_ndigis ; n++)
		make_rose->source_digis[n]= facilities.source_digis[n];
	make_rose->neighbour     = neigh;
	make_rose->device        = dev;
	make_rose->facilities    = facilities;

	make_rose->neighbour->use++;

	if (rose_sk(sk)->defer) {
		make_rose->state = ROSE_STATE_5;
	} else {
		rose_write_internal(make, ROSE_CALL_ACCEPTED);
		make_rose->state = ROSE_STATE_3;
		rose_start_idletimer(make);
	}

	make_rose->condition = 0x00;
	make_rose->vs        = 0;
	make_rose->va        = 0;
	make_rose->vr        = 0;
	make_rose->vl        = 0;
	sk->sk_ack_backlog++;

	rose_insert_socket(make);

	skb_queue_head(&sk->sk_receive_queue, skb);

	rose_start_heartbeat(make);

	if (!sock_flag(sk, SOCK_DEAD))
		sk->sk_data_ready(sk, skb->len);

	return 1;
}