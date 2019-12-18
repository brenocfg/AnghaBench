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
union skb_shared_tx {int hardware; int software; scalar_t__ flags; } ;
struct sock {int dummy; } ;
struct msghdr {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SOCK_TIMESTAMPING_TX_HARDWARE ; 
 int /*<<< orphan*/  SOCK_TIMESTAMPING_TX_SOFTWARE ; 
 scalar_t__ sock_flag (struct sock*,int /*<<< orphan*/ ) ; 

int sock_tx_timestamp(struct msghdr *msg, struct sock *sk,
		      union skb_shared_tx *shtx)
{
	shtx->flags = 0;
	if (sock_flag(sk, SOCK_TIMESTAMPING_TX_HARDWARE))
		shtx->hardware = 1;
	if (sock_flag(sk, SOCK_TIMESTAMPING_TX_SOFTWARE))
		shtx->software = 1;
	return 0;
}