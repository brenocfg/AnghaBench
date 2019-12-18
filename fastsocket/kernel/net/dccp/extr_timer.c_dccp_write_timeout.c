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
struct sock {scalar_t__ sk_state; int /*<<< orphan*/  sk_dst_cache; } ;
struct inet_connection_sock {int icsk_retransmits; scalar_t__ icsk_syn_retries; } ;

/* Variables and functions */
 scalar_t__ DCCP_PARTOPEN ; 
 scalar_t__ DCCP_REQUESTING ; 
 int /*<<< orphan*/  dccp_write_err (struct sock*) ; 
 int /*<<< orphan*/  dst_negative_advice (int /*<<< orphan*/ *) ; 
 struct inet_connection_sock* inet_csk (struct sock*) ; 
 int sysctl_dccp_request_retries ; 
 int sysctl_dccp_retries1 ; 
 int sysctl_dccp_retries2 ; 

__attribute__((used)) static int dccp_write_timeout(struct sock *sk)
{
	const struct inet_connection_sock *icsk = inet_csk(sk);
	int retry_until;

	if (sk->sk_state == DCCP_REQUESTING || sk->sk_state == DCCP_PARTOPEN) {
		if (icsk->icsk_retransmits != 0)
			dst_negative_advice(&sk->sk_dst_cache);
		retry_until = icsk->icsk_syn_retries ?
			    : sysctl_dccp_request_retries;
	} else {
		if (icsk->icsk_retransmits >= sysctl_dccp_retries1) {
			/* NOTE. draft-ietf-tcpimpl-pmtud-01.txt requires pmtu
			   black hole detection. :-(

			   It is place to make it. It is not made. I do not want
			   to make it. It is disguisting. It does not work in any
			   case. Let me to cite the same draft, which requires for
			   us to implement this:

   "The one security concern raised by this memo is that ICMP black holes
   are often caused by over-zealous security administrators who block
   all ICMP messages.  It is vitally important that those who design and
   deploy security systems understand the impact of strict filtering on
   upper-layer protocols.  The safest web site in the world is worthless
   if most TCP implementations cannot transfer data from it.  It would
   be far nicer to have all of the black holes fixed rather than fixing
   all of the TCP implementations."

			   Golden words :-).
		   */

			dst_negative_advice(&sk->sk_dst_cache);
		}

		retry_until = sysctl_dccp_retries2;
		/*
		 * FIXME: see tcp_write_timout and tcp_out_of_resources
		 */
	}

	if (icsk->icsk_retransmits >= retry_until) {
		/* Has it gone just too far? */
		dccp_write_err(sk);
		return 1;
	}
	return 0;
}