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
struct tcp_out_options {unsigned int mss; int /*<<< orphan*/  options; int /*<<< orphan*/  tsecr; int /*<<< orphan*/  tsval; int /*<<< orphan*/  ws; } ;
struct tcp_md5sig_key {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct request_sock {int /*<<< orphan*/  ts_recent; } ;
struct inet_request_sock {char sack_ok; char wscale_ok; int /*<<< orphan*/  rcv_wscale; scalar_t__ tstamp_ok; } ;
struct TYPE_6__ {int /*<<< orphan*/  when; } ;
struct TYPE_5__ {TYPE_1__* af_specific; } ;
struct TYPE_4__ {struct tcp_md5sig_key* (* md5_lookup ) (struct sock*,struct request_sock*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  OPTION_MD5 ; 
 int /*<<< orphan*/  OPTION_SACK_ADVERTISE ; 
 int /*<<< orphan*/  OPTION_TS ; 
 int /*<<< orphan*/  OPTION_WSCALE ; 
 scalar_t__ TCPOLEN_MD5SIG_ALIGNED ; 
 scalar_t__ TCPOLEN_MSS_ALIGNED ; 
 scalar_t__ TCPOLEN_SACKPERM_ALIGNED ; 
 scalar_t__ TCPOLEN_TSTAMP_ALIGNED ; 
 scalar_t__ TCPOLEN_WSCALE_ALIGNED ; 
 TYPE_3__* TCP_SKB_CB (struct sk_buff*) ; 
 struct inet_request_sock* inet_rsk (struct request_sock*) ; 
 scalar_t__ likely (char) ; 
 struct tcp_md5sig_key* stub1 (struct sock*,struct request_sock*) ; 
 TYPE_2__* tcp_rsk (struct request_sock*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static unsigned tcp_synack_options(struct sock *sk,
				   struct request_sock *req,
				   unsigned mss, struct sk_buff *skb,
				   struct tcp_out_options *opts,
				   struct tcp_md5sig_key **md5) {
	unsigned size = 0;
	struct inet_request_sock *ireq = inet_rsk(req);
	char doing_ts;

#ifdef CONFIG_TCP_MD5SIG
	*md5 = tcp_rsk(req)->af_specific->md5_lookup(sk, req);
	if (*md5) {
		opts->options |= OPTION_MD5;
		size += TCPOLEN_MD5SIG_ALIGNED;
	}
#else
	*md5 = NULL;
#endif

	/* we can't fit any SACK blocks in a packet with MD5 + TS
	   options. There was discussion about disabling SACK rather than TS in
	   order to fit in better with old, buggy kernels, but that was deemed
	   to be unnecessary. */
	doing_ts = ireq->tstamp_ok && !(*md5 && ireq->sack_ok);

	opts->mss = mss;
	size += TCPOLEN_MSS_ALIGNED;

	if (likely(ireq->wscale_ok)) {
		opts->ws = ireq->rcv_wscale;
		opts->options |= OPTION_WSCALE;
		size += TCPOLEN_WSCALE_ALIGNED;
	}
	if (likely(doing_ts)) {
		opts->options |= OPTION_TS;
		opts->tsval = TCP_SKB_CB(skb)->when;
		opts->tsecr = req->ts_recent;
		size += TCPOLEN_TSTAMP_ALIGNED;
	}
	if (likely(ireq->sack_ok)) {
		opts->options |= OPTION_SACK_ADVERTISE;
		if (unlikely(!doing_ts))
			size += TCPOLEN_SACKPERM_ALIGNED;
	}

	return size;
}