#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct socket {int /*<<< orphan*/ * ops; } ;
struct sock {int sk_no_check; int /*<<< orphan*/  sk_rcvbuf; int /*<<< orphan*/  sk_sndbuf; int /*<<< orphan*/  sk_allocation; scalar_t__ sk_protocol; int /*<<< orphan*/  sk_family; int /*<<< orphan*/  sk_destruct; int /*<<< orphan*/  sk_backlog_rcv; } ;
struct net {int dummy; } ;
struct TYPE_6__ {int acc_accl; int /*<<< orphan*/  acc_acc; } ;
struct TYPE_5__ {void* sdn_family; } ;
struct TYPE_4__ {void* sdn_family; } ;
struct dn_scp {int numdat; int numoth; int flowrem_oth; int flowloc_oth; int services_loc; int info_loc; int multi_ireq; int keepalive; int /*<<< orphan*/  delack_fxn; scalar_t__ delack_pending; int /*<<< orphan*/  delack_timer; int /*<<< orphan*/  keepalive_fxn; int /*<<< orphan*/ * persist_fxn; scalar_t__ persist; int /*<<< orphan*/  other_receive_queue; int /*<<< orphan*/  other_xmit_queue; int /*<<< orphan*/  data_xmit_queue; scalar_t__ nsp_rxtshift; int /*<<< orphan*/  nsp_rttvar; int /*<<< orphan*/  nsp_srtt; int /*<<< orphan*/  snd_window; int /*<<< orphan*/  max_window; TYPE_3__ accessdata; TYPE_2__ peer; TYPE_1__ addr; int /*<<< orphan*/  accept_mode; scalar_t__ nonagle; scalar_t__ segsize_rem; scalar_t__ info_rem; scalar_t__ services_rem; scalar_t__ flowloc_dat; scalar_t__ flowrem_dat; void* flowloc_sw; void* flowrem_sw; scalar_t__ ackrcv_oth; scalar_t__ ackrcv_dat; scalar_t__ ackxmt_oth; scalar_t__ ackxmt_dat; int /*<<< orphan*/  state; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  ACC_IMMED ; 
 void* AF_DECnet ; 
 scalar_t__ DN_MAX_NSP_DATA_HEADER ; 
 int /*<<< orphan*/  DN_O ; 
 void* DN_SEND ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 int HZ ; 
 int NSP_FC_NONE ; 
 int /*<<< orphan*/  NSP_INITIAL_RTTVAR ; 
 int /*<<< orphan*/  NSP_INITIAL_SRTT ; 
 int /*<<< orphan*/  NSP_MAX_WINDOW ; 
 int /*<<< orphan*/  NSP_MIN_WINDOW ; 
 int /*<<< orphan*/  PF_DECnet ; 
 int /*<<< orphan*/  dn_destruct ; 
 int /*<<< orphan*/  dn_keepalive ; 
 int /*<<< orphan*/  dn_nsp_backlog_rcv ; 
 int /*<<< orphan*/  dn_nsp_delayed_ack ; 
 int /*<<< orphan*/  dn_proto ; 
 int /*<<< orphan*/  dn_proto_ops ; 
 int /*<<< orphan*/  dn_start_slow_timer (struct sock*) ; 
 int /*<<< orphan*/  init_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char*,int) ; 
 struct sock* sk_alloc (struct net*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_head_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sock_init_data (struct socket*,struct sock*) ; 
 int /*<<< orphan*/ * sysctl_decnet_rmem ; 
 int /*<<< orphan*/ * sysctl_decnet_wmem ; 

__attribute__((used)) static struct sock *dn_alloc_sock(struct net *net, struct socket *sock, gfp_t gfp)
{
	struct dn_scp *scp;
	struct sock *sk = sk_alloc(net, PF_DECnet, gfp, &dn_proto);

	if  (!sk)
		goto out;

	if (sock)
		sock->ops = &dn_proto_ops;
	sock_init_data(sock, sk);

	sk->sk_backlog_rcv = dn_nsp_backlog_rcv;
	sk->sk_destruct    = dn_destruct;
	sk->sk_no_check    = 1;
	sk->sk_family      = PF_DECnet;
	sk->sk_protocol    = 0;
	sk->sk_allocation  = gfp;
	sk->sk_sndbuf	   = sysctl_decnet_wmem[1];
	sk->sk_rcvbuf	   = sysctl_decnet_rmem[1];

	/* Initialization of DECnet Session Control Port		*/
	scp = DN_SK(sk);
	scp->state	= DN_O;		/* Open			*/
	scp->numdat	= 1;		/* Next data seg to tx	*/
	scp->numoth	= 1;		/* Next oth data to tx  */
	scp->ackxmt_dat = 0;		/* Last data seg ack'ed */
	scp->ackxmt_oth = 0;		/* Last oth data ack'ed */
	scp->ackrcv_dat = 0;		/* Highest data ack recv*/
	scp->ackrcv_oth = 0;		/* Last oth data ack rec*/
	scp->flowrem_sw = DN_SEND;
	scp->flowloc_sw = DN_SEND;
	scp->flowrem_dat = 0;
	scp->flowrem_oth = 1;
	scp->flowloc_dat = 0;
	scp->flowloc_oth = 1;
	scp->services_rem = 0;
	scp->services_loc = 1 | NSP_FC_NONE;
	scp->info_rem = 0;
	scp->info_loc = 0x03; /* NSP version 4.1 */
	scp->segsize_rem = 230 - DN_MAX_NSP_DATA_HEADER; /* Default: Updated by remote segsize */
	scp->nonagle = 0;
	scp->multi_ireq = 1;
	scp->accept_mode = ACC_IMMED;
	scp->addr.sdn_family    = AF_DECnet;
	scp->peer.sdn_family    = AF_DECnet;
	scp->accessdata.acc_accl = 5;
	memcpy(scp->accessdata.acc_acc, "LINUX", 5);

	scp->max_window   = NSP_MAX_WINDOW;
	scp->snd_window   = NSP_MIN_WINDOW;
	scp->nsp_srtt     = NSP_INITIAL_SRTT;
	scp->nsp_rttvar   = NSP_INITIAL_RTTVAR;
	scp->nsp_rxtshift = 0;

	skb_queue_head_init(&scp->data_xmit_queue);
	skb_queue_head_init(&scp->other_xmit_queue);
	skb_queue_head_init(&scp->other_receive_queue);

	scp->persist = 0;
	scp->persist_fxn = NULL;
	scp->keepalive = 10 * HZ;
	scp->keepalive_fxn = dn_keepalive;

	init_timer(&scp->delack_timer);
	scp->delack_pending = 0;
	scp->delack_fxn = dn_nsp_delayed_ack;

	dn_start_slow_timer(sk);
out:
	return sk;
}