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
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_err; int /*<<< orphan*/  sk_route_caps; int /*<<< orphan*/  sk_dst_cache; int /*<<< orphan*/  sk_bound_dev_if; } ;
struct sk_buff {struct sock* sk; } ;
struct flowi {int /*<<< orphan*/  proto; void* fld_dst; void* fld_src; int /*<<< orphan*/  oif; } ;
struct dst_entry {TYPE_1__* dev; } ;
struct dn_scp {int /*<<< orphan*/  peer; int /*<<< orphan*/  addr; int /*<<< orphan*/  stamp; } ;
typedef  int /*<<< orphan*/  fl ;
struct TYPE_2__ {int /*<<< orphan*/  features; } ;

/* Variables and functions */
 int /*<<< orphan*/  DNPROTO_NSP ; 
 struct dn_scp* DN_SK (struct sock*) ; 
 int /*<<< orphan*/  EHOSTUNREACH ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 scalar_t__ dn_route_output_sock (int /*<<< orphan*/ *,struct flowi*,struct sock*,int /*<<< orphan*/ ) ; 
 void* dn_saddr2dn (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dn_sk_ports_copy (struct flowi*,struct dn_scp*) ; 
 int /*<<< orphan*/  dst_output (struct sk_buff*) ; 
 int /*<<< orphan*/  jiffies ; 
 int /*<<< orphan*/  memset (struct flowi*,int /*<<< orphan*/ ,int) ; 
 struct dst_entry* sk_dst_check (struct sock*,int /*<<< orphan*/ ) ; 
 struct dst_entry* sk_dst_get (struct sock*) ; 
 int /*<<< orphan*/  skb_dst_set (struct sk_buff*,struct dst_entry*) ; 
 int /*<<< orphan*/  skb_reset_transport_header (struct sk_buff*) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 

__attribute__((used)) static void dn_nsp_send(struct sk_buff *skb)
{
	struct sock *sk = skb->sk;
	struct dn_scp *scp = DN_SK(sk);
	struct dst_entry *dst;
	struct flowi fl;

	skb_reset_transport_header(skb);
	scp->stamp = jiffies;

	dst = sk_dst_check(sk, 0);
	if (dst) {
try_again:
		skb_dst_set(skb, dst);
		dst_output(skb);
		return;
	}

	memset(&fl, 0, sizeof(fl));
	fl.oif = sk->sk_bound_dev_if;
	fl.fld_src = dn_saddr2dn(&scp->addr);
	fl.fld_dst = dn_saddr2dn(&scp->peer);
	dn_sk_ports_copy(&fl, scp);
	fl.proto = DNPROTO_NSP;
	if (dn_route_output_sock(&sk->sk_dst_cache, &fl, sk, 0) == 0) {
		dst = sk_dst_get(sk);
		sk->sk_route_caps = dst->dev->features;
		goto try_again;
	}

	sk->sk_err = EHOSTUNREACH;
	if (!sock_flag(sk, SOCK_DEAD))
		sk->sk_state_change(sk);
}