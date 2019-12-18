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
typedef  int u32 ;
struct vegas {int /*<<< orphan*/  minRTT; int /*<<< orphan*/  baseRTT; int /*<<< orphan*/  cntRTT; int /*<<< orphan*/  doing_vegas_now; } ;
struct tcpvegas_info {int /*<<< orphan*/  tcpv_minrtt; int /*<<< orphan*/  tcpv_rtt; int /*<<< orphan*/  tcpv_rttcnt; int /*<<< orphan*/  tcpv_enabled; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  info ;

/* Variables and functions */
 int INET_DIAG_VEGASINFO ; 
 struct vegas* inet_csk_ca (struct sock*) ; 
 int /*<<< orphan*/  nla_put (struct sk_buff*,int,int,struct tcpvegas_info*) ; 

void tcp_vegas_get_info(struct sock *sk, u32 ext, struct sk_buff *skb)
{
	const struct vegas *ca = inet_csk_ca(sk);
	if (ext & (1 << (INET_DIAG_VEGASINFO - 1))) {
		struct tcpvegas_info info = {
			.tcpv_enabled = ca->doing_vegas_now,
			.tcpv_rttcnt = ca->cntRTT,
			.tcpv_rtt = ca->baseRTT,
			.tcpv_minrtt = ca->minRTT,
		};

		nla_put(skb, INET_DIAG_VEGASINFO, sizeof(info), &info);
	}
}