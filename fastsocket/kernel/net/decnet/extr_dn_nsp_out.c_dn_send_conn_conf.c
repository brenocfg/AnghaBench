#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nsp_conn_init_msg {int msgflg; int /*<<< orphan*/  segsize; int /*<<< orphan*/  info; int /*<<< orphan*/  services; int /*<<< orphan*/  srcaddr; int /*<<< orphan*/  dstaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  opt_data; int /*<<< orphan*/  opt_optl; } ;
struct dn_scp {int /*<<< orphan*/  persist_fxn; int /*<<< orphan*/  persist; TYPE_1__ conndata_out; int /*<<< orphan*/  segsize_loc; int /*<<< orphan*/  info_loc; int /*<<< orphan*/  services_loc; int /*<<< orphan*/  addrloc; int /*<<< orphan*/  addrrem; } ;
typedef  int /*<<< orphan*/  gfp_t ;
typedef  int __u8 ;

/* Variables and functions */
 struct dn_scp* DN_SK (struct sock*) ; 
 int /*<<< orphan*/  cpu_to_le16 (int /*<<< orphan*/ ) ; 
 struct sk_buff* dn_alloc_skb (struct sock*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dn_nsp_persist (struct sock*) ; 
 int /*<<< orphan*/  dn_nsp_retrans_conn_conf ; 
 int /*<<< orphan*/  dn_nsp_send (struct sk_buff*) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int* skb_put (struct sk_buff*,int) ; 

void dn_send_conn_conf(struct sock *sk, gfp_t gfp)
{
	struct dn_scp *scp = DN_SK(sk);
	struct sk_buff *skb = NULL;
	struct nsp_conn_init_msg *msg;
	__u8 len = (__u8)le16_to_cpu(scp->conndata_out.opt_optl);

	if ((skb = dn_alloc_skb(sk, 50 + len, gfp)) == NULL)
		return;

	msg = (struct nsp_conn_init_msg *)skb_put(skb, sizeof(*msg));
	msg->msgflg = 0x28;
	msg->dstaddr = scp->addrrem;
	msg->srcaddr = scp->addrloc;
	msg->services = scp->services_loc;
	msg->info = scp->info_loc;
	msg->segsize = cpu_to_le16(scp->segsize_loc);

	*skb_put(skb,1) = len;

	if (len > 0)
		memcpy(skb_put(skb, len), scp->conndata_out.opt_data, len);


	dn_nsp_send(skb);

	scp->persist = dn_nsp_persist(sk);
	scp->persist_fxn = dn_nsp_retrans_conn_conf;
}