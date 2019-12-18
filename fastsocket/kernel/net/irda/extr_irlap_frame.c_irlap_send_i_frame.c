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
struct sk_buff {int* data; } ;
struct irlap_cb {int caddr; int vr; } ;

/* Variables and functions */
 int CMD_FRAME ; 
 int /*<<< orphan*/  irlap_queue_xmit (struct irlap_cb*,struct sk_buff*) ; 

__attribute__((used)) static void irlap_send_i_frame(struct irlap_cb *self, struct sk_buff *skb,
			       int command)
{
	/* Insert connection address */
	skb->data[0] = self->caddr;
	skb->data[0] |= (command) ? CMD_FRAME : 0;

	/* Insert next to receive (Vr) */
	skb->data[1] |= (self->vr << 5);  /* insert nr */

	irlap_queue_xmit(self, skb);
}