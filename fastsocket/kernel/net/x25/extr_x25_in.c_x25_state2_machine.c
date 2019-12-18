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
struct sock {int dummy; } ;
struct sk_buff {int /*<<< orphan*/ * data; } ;

/* Variables and functions */
#define  X25_CLEAR_CONFIRMATION 129 
#define  X25_CLEAR_REQUEST 128 
 int /*<<< orphan*/  x25_disconnect (struct sock*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  x25_write_internal (struct sock*,int) ; 

__attribute__((used)) static int x25_state2_machine(struct sock *sk, struct sk_buff *skb, int frametype)
{
	switch (frametype) {

		case X25_CLEAR_REQUEST:
			x25_write_internal(sk, X25_CLEAR_CONFIRMATION);
			x25_disconnect(sk, 0, skb->data[3], skb->data[4]);
			break;

		case X25_CLEAR_CONFIRMATION:
			x25_disconnect(sk, 0, 0, 0);
			break;

		default:
			break;
	}

	return 0;
}