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
struct l2cap_sig {TYPE_1__* p; } ;
struct l2cap_pcb {int /*<<< orphan*/  remote_bdaddr; } ;
typedef  int /*<<< orphan*/  err_t ;
struct TYPE_2__ {int /*<<< orphan*/  tot_len; } ;

/* Variables and functions */
 int /*<<< orphan*/  l2cap_write (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 

err_t l2cap_rexmit_signal(struct l2cap_pcb *pcb, struct l2cap_sig *sig)
{
	err_t ret;

	/* Set up L2CAP hdr */
	ret = l2cap_write(&(pcb->remote_bdaddr), sig->p, sig->p->tot_len); /* Send peer L2CAP signal */

	return ret;
}