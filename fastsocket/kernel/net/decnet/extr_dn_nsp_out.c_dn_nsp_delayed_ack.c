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
struct dn_scp {scalar_t__ ackxmt_oth; scalar_t__ numoth_rcv; scalar_t__ ackxmt_dat; scalar_t__ numdat_rcv; } ;

/* Variables and functions */
 struct dn_scp* DN_SK (struct sock*) ; 
 int /*<<< orphan*/  dn_nsp_send_data_ack (struct sock*) ; 
 int /*<<< orphan*/  dn_nsp_send_oth_ack (struct sock*) ; 

void dn_nsp_delayed_ack(struct sock *sk)
{
	struct dn_scp *scp = DN_SK(sk);

	if (scp->ackxmt_oth != scp->numoth_rcv)
		dn_nsp_send_oth_ack(sk);

	if (scp->ackxmt_dat != scp->numdat_rcv)
		dn_nsp_send_data_ack(sk);
}