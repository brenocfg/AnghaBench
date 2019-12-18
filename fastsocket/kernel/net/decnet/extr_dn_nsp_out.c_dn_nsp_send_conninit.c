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
struct sock {int /*<<< orphan*/  sk_allocation; } ;
struct sk_buff {int dummy; } ;
struct nsp_conn_init_msg {unsigned char msgflg; int dstaddr; int /*<<< orphan*/  segsize; int /*<<< orphan*/  info; int /*<<< orphan*/  services; int /*<<< orphan*/  srcaddr; } ;
struct dn_skb_cb {int /*<<< orphan*/  rt_flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  opt_data; int /*<<< orphan*/  opt_optl; } ;
struct TYPE_4__ {unsigned char acc_userl; unsigned char acc_passl; unsigned char acc_accl; int /*<<< orphan*/  acc_acc; int /*<<< orphan*/  acc_pass; int /*<<< orphan*/  acc_user; } ;
struct TYPE_6__ {int sdn_flags; scalar_t__ sdn_objnum; } ;
struct dn_scp {int /*<<< orphan*/  persist_fxn; int /*<<< orphan*/  persist; TYPE_2__ conndata_out; TYPE_1__ accessdata; TYPE_3__ peer; TYPE_3__ addr; int /*<<< orphan*/  segsize_loc; int /*<<< orphan*/  info_loc; int /*<<< orphan*/  services_loc; int /*<<< orphan*/  addrloc; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  unsigned char __u8 ;

/* Variables and functions */
 unsigned char DN_MENUVER_ACC ; 
 unsigned char DN_MENUVER_PRX ; 
 unsigned char DN_MENUVER_UIC ; 
 unsigned char DN_MENUVER_USR ; 
 int /*<<< orphan*/  DN_RT_F_RQR ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 struct dn_skb_cb* DN_SKB_CB (struct sk_buff*) ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 unsigned char NSP_CI ; 
 int SDF_PROXY ; 
 int SDF_UICPROXY ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dn_alloc_skb (struct sock*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_nsp_persist (struct sock*) ; 
 int /*<<< orphan*/  dn_nsp_retrans_conninit ; 
 int /*<<< orphan*/  dn_nsp_send (struct sk_buff*) ; 
 unsigned char dn_sockaddr2username (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ ,unsigned char) ; 
 unsigned char* skb_put (struct sk_buff*,unsigned char) ; 
 int /*<<< orphan*/  skb_tail_pointer (struct sk_buff*) ; 

void dn_nsp_send_conninit(struct sock *sk, unsigned char msgflg)
{
	struct dn_scp *scp = DN_SK(sk);
	struct nsp_conn_init_msg *msg;
	unsigned char aux;
	unsigned char menuver;
	struct dn_skb_cb *cb;
	unsigned char type = 1;
	gfp_t allocation = (msgflg == NSP_CI) ? sk->sk_allocation : GFP_ATOMIC;
	struct sk_buff *skb = dn_alloc_skb(sk, 200, allocation);

	if (!skb)
		return;

	cb  = DN_SKB_CB(skb);
	msg = (struct nsp_conn_init_msg *)skb_put(skb,sizeof(*msg));

	msg->msgflg	= msgflg;
	msg->dstaddr	= 0x0000;		/* Remote Node will assign it*/

	msg->srcaddr	= scp->addrloc;
	msg->services	= scp->services_loc;	/* Requested flow control    */
	msg->info	= scp->info_loc;	/* Version Number            */
	msg->segsize	= cpu_to_le16(scp->segsize_loc);	/* Max segment size  */

	if (scp->peer.sdn_objnum)
		type = 0;

	skb_put(skb, dn_sockaddr2username(&scp->peer,
					  skb_tail_pointer(skb), type));
	skb_put(skb, dn_sockaddr2username(&scp->addr,
					  skb_tail_pointer(skb), 2));

	menuver = DN_MENUVER_ACC | DN_MENUVER_USR;
	if (scp->peer.sdn_flags & SDF_PROXY)
		menuver |= DN_MENUVER_PRX;
	if (scp->peer.sdn_flags & SDF_UICPROXY)
		menuver |= DN_MENUVER_UIC;

	*skb_put(skb, 1) = menuver;	/* Menu Version		*/

	aux = scp->accessdata.acc_userl;
	*skb_put(skb, 1) = aux;
	if (aux > 0)
	memcpy(skb_put(skb, aux), scp->accessdata.acc_user, aux);

	aux = scp->accessdata.acc_passl;
	*skb_put(skb, 1) = aux;
	if (aux > 0)
	memcpy(skb_put(skb, aux), scp->accessdata.acc_pass, aux);

	aux = scp->accessdata.acc_accl;
	*skb_put(skb, 1) = aux;
	if (aux > 0)
	memcpy(skb_put(skb, aux), scp->accessdata.acc_acc, aux);

	aux = (__u8)le16_to_cpu(scp->conndata_out.opt_optl);
	*skb_put(skb, 1) = aux;
	if (aux > 0)
	memcpy(skb_put(skb,aux), scp->conndata_out.opt_data, aux);

	scp->persist = dn_nsp_persist(sk);
	scp->persist_fxn = dn_nsp_retrans_conninit;

	cb->rt_flags = DN_RT_F_RQR;

	dn_nsp_send(skb);
}