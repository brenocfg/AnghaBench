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
typedef  int /*<<< orphan*/  theirs ;
struct x25_facilities {int reverse; scalar_t__ throughput; scalar_t__ pacsize_in; scalar_t__ pacsize_out; scalar_t__ winsize_in; scalar_t__ winsize_out; } ;
struct x25_sock {int /*<<< orphan*/  vc_facil_mask; struct x25_facilities facilities; } ;
struct x25_dte_facilities {int dummy; } ;
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_DEBUG (struct sock*,char*) ; 
 int /*<<< orphan*/  memcpy (struct x25_facilities*,struct x25_facilities*,int) ; 
 int /*<<< orphan*/  memset (struct x25_facilities*,int /*<<< orphan*/ ,int) ; 
 int x25_parse_facilities (struct sk_buff*,struct x25_facilities*,struct x25_dte_facilities*,int /*<<< orphan*/ *) ; 
 struct x25_sock* x25_sk (struct sock*) ; 

int x25_negotiate_facilities(struct sk_buff *skb, struct sock *sk,
		struct x25_facilities *new, struct x25_dte_facilities *dte)
{
	struct x25_sock *x25 = x25_sk(sk);
	struct x25_facilities *ours = &x25->facilities;
	struct x25_facilities theirs;
	int len;

	memset(&theirs, 0, sizeof(theirs));
	memcpy(new, ours, sizeof(*new));

	len = x25_parse_facilities(skb, &theirs, dte, &x25->vc_facil_mask);

	/*
	 *	They want reverse charging, we won't accept it.
	 */
	if ((theirs.reverse & 0x01 ) && (ours->reverse & 0x01)) {
		SOCK_DEBUG(sk, "X.25: rejecting reverse charging request\n");
		return -1;
	}

	new->reverse = theirs.reverse;

	if (theirs.throughput) {
		if (theirs.throughput < ours->throughput) {
			SOCK_DEBUG(sk, "X.25: throughput negotiated down\n");
			new->throughput = theirs.throughput;
		}
	}

	if (theirs.pacsize_in && theirs.pacsize_out) {
		if (theirs.pacsize_in < ours->pacsize_in) {
			SOCK_DEBUG(sk, "X.25: packet size inwards negotiated down\n");
			new->pacsize_in = theirs.pacsize_in;
		}
		if (theirs.pacsize_out < ours->pacsize_out) {
			SOCK_DEBUG(sk, "X.25: packet size outwards negotiated down\n");
			new->pacsize_out = theirs.pacsize_out;
		}
	}

	if (theirs.winsize_in && theirs.winsize_out) {
		if (theirs.winsize_in < ours->winsize_in) {
			SOCK_DEBUG(sk, "X.25: window size inwards negotiated down\n");
			new->winsize_in = theirs.winsize_in;
		}
		if (theirs.winsize_out < ours->winsize_out) {
			SOCK_DEBUG(sk, "X.25: window size outwards negotiated down\n");
			new->winsize_out = theirs.winsize_out;
		}
	}

	return len;
}