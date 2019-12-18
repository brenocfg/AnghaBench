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
struct TYPE_2__ {int /*<<< orphan*/  cudlength; int /*<<< orphan*/  cuddata; } ;
struct x25_sock {int condition; TYPE_1__ calluserdata; int /*<<< orphan*/  vc_facil_mask; int /*<<< orphan*/  dte_facilities; int /*<<< orphan*/  facilities; int /*<<< orphan*/  state; int /*<<< orphan*/  vl; int /*<<< orphan*/  vr; int /*<<< orphan*/  va; int /*<<< orphan*/  vs; } ;
struct x25_address {int dummy; } ;
struct sock {int /*<<< orphan*/  (* sk_state_change ) (struct sock*) ;int /*<<< orphan*/  sk_state; } ;
struct sk_buff {int /*<<< orphan*/ * data; int /*<<< orphan*/  len; } ;

/* Variables and functions */
 int /*<<< orphan*/  ECONNREFUSED ; 
 int /*<<< orphan*/  SOCK_DEAD ; 
 int /*<<< orphan*/  TCP_ESTABLISHED ; 
#define  X25_CALL_ACCEPTED 129 
 int /*<<< orphan*/  X25_CLEAR_CONFIRMATION ; 
#define  X25_CLEAR_REQUEST 128 
 int /*<<< orphan*/  X25_STATE_3 ; 
 int /*<<< orphan*/  X25_STD_MIN_LEN ; 
 int /*<<< orphan*/  skb_copy_from_linear_data (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_pull (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sock_flag (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct sock*) ; 
 int /*<<< orphan*/  x25_addr_ntoa (int /*<<< orphan*/ *,struct x25_address*,struct x25_address*) ; 
 int /*<<< orphan*/  x25_disconnect (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x25_parse_facilities (struct sk_buff*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct x25_sock* x25_sk (struct sock*) ; 
 int /*<<< orphan*/  x25_stop_timer (struct sock*) ; 
 int /*<<< orphan*/  x25_write_internal (struct sock*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int x25_state1_machine(struct sock *sk, struct sk_buff *skb, int frametype)
{
	struct x25_address source_addr, dest_addr;

	switch (frametype) {
		case X25_CALL_ACCEPTED: {
			struct x25_sock *x25 = x25_sk(sk);

			x25_stop_timer(sk);
			x25->condition = 0x00;
			x25->vs        = 0;
			x25->va        = 0;
			x25->vr        = 0;
			x25->vl        = 0;
			x25->state     = X25_STATE_3;
			sk->sk_state   = TCP_ESTABLISHED;
			/*
			 *	Parse the data in the frame.
			 */
			skb_pull(skb, X25_STD_MIN_LEN);
			skb_pull(skb, x25_addr_ntoa(skb->data, &source_addr, &dest_addr));
			skb_pull(skb,
				 x25_parse_facilities(skb, &x25->facilities,
						&x25->dte_facilities,
						&x25->vc_facil_mask));
			/*
			 *	Copy any Call User Data.
			 */
			if (skb->len >= 0) {
				skb_copy_from_linear_data(skb,
					      x25->calluserdata.cuddata,
					      skb->len);
				x25->calluserdata.cudlength = skb->len;
			}
			if (!sock_flag(sk, SOCK_DEAD))
				sk->sk_state_change(sk);
			break;
		}
		case X25_CLEAR_REQUEST:
			x25_write_internal(sk, X25_CLEAR_CONFIRMATION);
			x25_disconnect(sk, ECONNREFUSED, skb->data[3], skb->data[4]);
			break;

		default:
			break;
	}

	return 0;
}