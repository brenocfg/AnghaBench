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
struct TYPE_2__ {scalar_t__ dsack; } ;
struct tcp_sock {TYPE_1__ rx_opt; struct tcp_sack_block* selective_acks; struct tcp_sack_block* duplicate_sack; } ;
struct tcp_sack_block {int start_seq; int end_seq; } ;
struct tcp_out_options {int options; int mss; int tsval; int tsecr; int ws; int num_sack_blocks; } ;
typedef  int /*<<< orphan*/  __u8 ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int OPTION_MD5 ; 
 int OPTION_SACK_ADVERTISE ; 
 int OPTION_TS ; 
 int OPTION_WSCALE ; 
 int TCPOLEN_MD5SIG ; 
 int TCPOLEN_MSS ; 
 int TCPOLEN_SACK_BASE ; 
 int TCPOLEN_SACK_PERBLOCK ; 
 int TCPOLEN_SACK_PERM ; 
 int TCPOLEN_TIMESTAMP ; 
 int TCPOLEN_WINDOW ; 
 int TCPOPT_MD5SIG ; 
 int TCPOPT_MSS ; 
 int TCPOPT_NOP ; 
 int TCPOPT_SACK ; 
 int TCPOPT_SACK_PERM ; 
 int TCPOPT_TIMESTAMP ; 
 int TCPOPT_WINDOW ; 
 void* htonl (int) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void tcp_options_write(__be32 *ptr, struct tcp_sock *tp,
			      const struct tcp_out_options *opts,
			      __u8 **md5_hash) {
	if (unlikely(OPTION_MD5 & opts->options)) {
		*ptr++ = htonl((TCPOPT_NOP << 24) |
			       (TCPOPT_NOP << 16) |
			       (TCPOPT_MD5SIG << 8) |
			       TCPOLEN_MD5SIG);
		*md5_hash = (__u8 *)ptr;
		ptr += 4;
	} else {
		*md5_hash = NULL;
	}

	if (unlikely(opts->mss)) {
		*ptr++ = htonl((TCPOPT_MSS << 24) |
			       (TCPOLEN_MSS << 16) |
			       opts->mss);
	}

	if (likely(OPTION_TS & opts->options)) {
		if (unlikely(OPTION_SACK_ADVERTISE & opts->options)) {
			*ptr++ = htonl((TCPOPT_SACK_PERM << 24) |
				       (TCPOLEN_SACK_PERM << 16) |
				       (TCPOPT_TIMESTAMP << 8) |
				       TCPOLEN_TIMESTAMP);
		} else {
			*ptr++ = htonl((TCPOPT_NOP << 24) |
				       (TCPOPT_NOP << 16) |
				       (TCPOPT_TIMESTAMP << 8) |
				       TCPOLEN_TIMESTAMP);
		}
		*ptr++ = htonl(opts->tsval);
		*ptr++ = htonl(opts->tsecr);
	}

	if (unlikely(OPTION_SACK_ADVERTISE & opts->options &&
		     !(OPTION_TS & opts->options))) {
		*ptr++ = htonl((TCPOPT_NOP << 24) |
			       (TCPOPT_NOP << 16) |
			       (TCPOPT_SACK_PERM << 8) |
			       TCPOLEN_SACK_PERM);
	}

	if (unlikely(OPTION_WSCALE & opts->options)) {
		*ptr++ = htonl((TCPOPT_NOP << 24) |
			       (TCPOPT_WINDOW << 16) |
			       (TCPOLEN_WINDOW << 8) |
			       opts->ws);
	}

	if (unlikely(opts->num_sack_blocks)) {
		struct tcp_sack_block *sp = tp->rx_opt.dsack ?
			tp->duplicate_sack : tp->selective_acks;
		int this_sack;

		*ptr++ = htonl((TCPOPT_NOP  << 24) |
			       (TCPOPT_NOP  << 16) |
			       (TCPOPT_SACK <<  8) |
			       (TCPOLEN_SACK_BASE + (opts->num_sack_blocks *
						     TCPOLEN_SACK_PERBLOCK)));

		for (this_sack = 0; this_sack < opts->num_sack_blocks;
		     ++this_sack) {
			*ptr++ = htonl(sp[this_sack].start_seq);
			*ptr++ = htonl(sp[this_sack].end_seq);
		}

		tp->rx_opt.dsack = 0;
	}
}