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
struct TYPE_5__ {int /*<<< orphan*/  rcv_wscale; int /*<<< orphan*/  ts_recent; } ;
struct tcp_sock {TYPE_2__ rx_opt; TYPE_1__* af_specific; } ;
struct tcp_out_options {int options; int /*<<< orphan*/  ws; int /*<<< orphan*/  tsecr; int /*<<< orphan*/  tsval; int /*<<< orphan*/  mss; } ;
struct tcp_md5sig_key {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  when; } ;
struct TYPE_4__ {struct tcp_md5sig_key* (* md5_lookup ) (struct sock*,struct sock*) ;} ;

/* Variables and functions */
 int OPTION_MD5 ; 
 int OPTION_SACK_ADVERTISE ; 
 int OPTION_TS ; 
 int OPTION_WSCALE ; 
 scalar_t__ TCPOLEN_MD5SIG_ALIGNED ; 
 scalar_t__ TCPOLEN_MSS_ALIGNED ; 
 scalar_t__ TCPOLEN_SACKPERM_ALIGNED ; 
 scalar_t__ TCPOLEN_TSTAMP_ALIGNED ; 
 scalar_t__ TCPOLEN_WSCALE_ALIGNED ; 
 TYPE_3__* TCP_SKB_CB (struct sk_buff*) ; 
 scalar_t__ likely (int) ; 
 struct tcp_md5sig_key* stub1 (struct sock*,struct sock*) ; 
 int sysctl_tcp_sack ; 
 scalar_t__ sysctl_tcp_timestamps ; 
 int sysctl_tcp_window_scaling ; 
 int /*<<< orphan*/  tcp_advertise_mss (struct sock*) ; 
 struct tcp_sock* tcp_sk (struct sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned tcp_syn_options(struct sock *sk, struct sk_buff *skb,
				struct tcp_out_options *opts,
				struct tcp_md5sig_key **md5) {
	struct tcp_sock *tp = tcp_sk(sk);
	unsigned size = 0;

#ifdef CONFIG_TCP_MD5SIG
	*md5 = tp->af_specific->md5_lookup(sk, sk);
	if (*md5) {
		opts->options |= OPTION_MD5;
		size += TCPOLEN_MD5SIG_ALIGNED;
	}
#else
	*md5 = NULL;
#endif

	/* We always get an MSS option.  The option bytes which will be seen in
	 * normal data packets should timestamps be used, must be in the MSS
	 * advertised.  But we subtract them from tp->mss_cache so that
	 * calculations in tcp_sendmsg are simpler etc.  So account for this
	 * fact here if necessary.  If we don't do this correctly, as a
	 * receiver we won't recognize data packets as being full sized when we
	 * should, and thus we won't abide by the delayed ACK rules correctly.
	 * SACKs don't matter, we never delay an ACK when we have any of those
	 * going out.  */
	opts->mss = tcp_advertise_mss(sk);
	size += TCPOLEN_MSS_ALIGNED;

	if (likely(sysctl_tcp_timestamps && *md5 == NULL)) {
		opts->options |= OPTION_TS;
		opts->tsval = TCP_SKB_CB(skb)->when;
		opts->tsecr = tp->rx_opt.ts_recent;
		size += TCPOLEN_TSTAMP_ALIGNED;
	}
	if (likely(sysctl_tcp_window_scaling)) {
		opts->ws = tp->rx_opt.rcv_wscale;
		opts->options |= OPTION_WSCALE;
		size += TCPOLEN_WSCALE_ALIGNED;
	}
	if (likely(sysctl_tcp_sack)) {
		opts->options |= OPTION_SACK_ADVERTISE;
		if (unlikely(!(OPTION_TS & opts->options)))
			size += TCPOLEN_SACKPERM_ALIGNED;
	}

	return size;
}