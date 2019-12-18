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
struct i1480u_tx {int /*<<< orphan*/  urb; scalar_t__ skb; struct i1480u_tx* buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_irq (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct i1480u_tx*) ; 
 int /*<<< orphan*/  usb_free_urb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void i1480u_tx_free(struct i1480u_tx *wtx)
{
	kfree(wtx->buf);
	if (wtx->skb)
		dev_kfree_skb_irq(wtx->skb);
	usb_free_urb(wtx->urb);
	kfree(wtx);
}