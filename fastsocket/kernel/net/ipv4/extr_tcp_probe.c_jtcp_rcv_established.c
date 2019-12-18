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
struct tcphdr {int dummy; } ;
struct tcp_sock {scalar_t__ snd_cwnd; int srtt; int /*<<< orphan*/  snd_wnd; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  snd_nxt; } ;
struct tcp_log {scalar_t__ snd_cwnd; int srtt; int /*<<< orphan*/  ssthresh; int /*<<< orphan*/  snd_wnd; int /*<<< orphan*/  snd_una; int /*<<< orphan*/  snd_nxt; int /*<<< orphan*/  length; int /*<<< orphan*/  dport; int /*<<< orphan*/  daddr; int /*<<< orphan*/  sport; int /*<<< orphan*/  saddr; int /*<<< orphan*/  tstamp; } ;
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;
struct inet_sock {int /*<<< orphan*/  dport; int /*<<< orphan*/  daddr; int /*<<< orphan*/  sport; int /*<<< orphan*/  saddr; } ;
struct TYPE_2__ {scalar_t__ lastcwnd; int head; int /*<<< orphan*/  wait; int /*<<< orphan*/  lock; struct tcp_log* log; } ;

/* Variables and functions */
 int bufsize ; 
 scalar_t__ full ; 
 struct inet_sock* inet_sk (struct sock*) ; 
 int /*<<< orphan*/  jprobe_return () ; 
 int /*<<< orphan*/  ktime_get () ; 
 scalar_t__ ntohs (int /*<<< orphan*/ ) ; 
 scalar_t__ port ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcp_current_ssthresh (struct sock*) ; 
 TYPE_1__ tcp_probe ; 
 int tcp_probe_avail () ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int jtcp_rcv_established(struct sock *sk, struct sk_buff *skb,
			       struct tcphdr *th, unsigned len)
{
	const struct tcp_sock *tp = tcp_sk(sk);
	const struct inet_sock *inet = inet_sk(sk);

	/* Only update if port matches */
	if ((port == 0 || ntohs(inet->dport) == port || ntohs(inet->sport) == port)
	    && (full || tp->snd_cwnd != tcp_probe.lastcwnd)) {

		spin_lock(&tcp_probe.lock);
		/* If log fills, just silently drop */
		if (tcp_probe_avail() > 1) {
			struct tcp_log *p = tcp_probe.log + tcp_probe.head;

			p->tstamp = ktime_get();
			p->saddr = inet->saddr;
			p->sport = inet->sport;
			p->daddr = inet->daddr;
			p->dport = inet->dport;
			p->length = skb->len;
			p->snd_nxt = tp->snd_nxt;
			p->snd_una = tp->snd_una;
			p->snd_cwnd = tp->snd_cwnd;
			p->snd_wnd = tp->snd_wnd;
			p->ssthresh = tcp_current_ssthresh(sk);
			p->srtt = tp->srtt >> 3;

			tcp_probe.head = (tcp_probe.head + 1) % bufsize;
		}
		tcp_probe.lastcwnd = tp->snd_cwnd;
		spin_unlock(&tcp_probe.lock);

		wake_up(&tcp_probe.wait);
	}

	jprobe_return();
	return 0;
}