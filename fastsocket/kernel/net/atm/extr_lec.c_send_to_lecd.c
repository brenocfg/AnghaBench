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
struct sock {int /*<<< orphan*/  (* sk_data_ready ) (struct sock*,int) ;int /*<<< orphan*/  sk_receive_queue; } ;
struct sk_buff {int len; int /*<<< orphan*/  truesize; scalar_t__ data; } ;
struct lec_priv {int /*<<< orphan*/  lecd; } ;
struct TYPE_3__ {int targetless_le_arp; int /*<<< orphan*/  atm_addr; int /*<<< orphan*/  mac_addr; } ;
struct TYPE_4__ {TYPE_1__ normal; } ;
struct atmlec_msg {int sizeoftlvs; TYPE_2__ content; int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  atmlec_msg_type ;

/* Variables and functions */
 int /*<<< orphan*/  ATM_ESA_LEN ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 struct sk_buff* alloc_skb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atm_force_charge (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct atmlec_msg*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int) ; 
 struct sock* sk_atm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 
 int /*<<< orphan*/  stub1 (struct sock*,int) ; 
 int /*<<< orphan*/  stub2 (struct sock*,int) ; 

__attribute__((used)) static int
send_to_lecd(struct lec_priv *priv, atmlec_msg_type type,
	     const unsigned char *mac_addr, const unsigned char *atm_addr,
	     struct sk_buff *data)
{
	struct sock *sk;
	struct sk_buff *skb;
	struct atmlec_msg *mesg;

	if (!priv || !priv->lecd) {
		return -1;
	}
	skb = alloc_skb(sizeof(struct atmlec_msg), GFP_ATOMIC);
	if (!skb)
		return -1;
	skb->len = sizeof(struct atmlec_msg);
	mesg = (struct atmlec_msg *)skb->data;
	memset(mesg, 0, sizeof(struct atmlec_msg));
	mesg->type = type;
	if (data != NULL)
		mesg->sizeoftlvs = data->len;
	if (mac_addr)
		memcpy(&mesg->content.normal.mac_addr, mac_addr, ETH_ALEN);
	else
		mesg->content.normal.targetless_le_arp = 1;
	if (atm_addr)
		memcpy(&mesg->content.normal.atm_addr, atm_addr, ATM_ESA_LEN);

	atm_force_charge(priv->lecd, skb->truesize);
	sk = sk_atm(priv->lecd);
	skb_queue_tail(&sk->sk_receive_queue, skb);
	sk->sk_data_ready(sk, skb->len);

	if (data != NULL) {
		pr_debug("lec: about to send %d bytes of data\n", data->len);
		atm_force_charge(priv->lecd, data->truesize);
		skb_queue_tail(&sk->sk_receive_queue, data);
		sk->sk_data_ready(sk, skb->len);
	}

	return 0;
}