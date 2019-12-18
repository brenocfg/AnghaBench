#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sixpack {int slottime; int status1; unsigned char persistence; int led_state; int tx_enable; int* xbuff; int status2; int xleft; int xhead; int /*<<< orphan*/  tx_t; TYPE_2__* tty; } ;
struct TYPE_6__ {TYPE_1__* ops; } ;
struct TYPE_5__ {int (* write ) (TYPE_2__*,int*,int) ;} ;

/* Variables and functions */
 int HZ ; 
 int SIXP_DCD_MASK ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int stub1 (TYPE_2__*,int*,int) ; 
 int stub2 (TYPE_2__*,int*,int) ; 
 int stub3 (TYPE_2__*,int*,int) ; 

__attribute__((used)) static void sp_xmit_on_air(unsigned long channel)
{
	struct sixpack *sp = (struct sixpack *) channel;
	int actual, when = sp->slottime;
	static unsigned char random;

	random = random * 17 + 41;

	if (((sp->status1 & SIXP_DCD_MASK) == 0) && (random < sp->persistence)) {
		sp->led_state = 0x70;
		sp->tty->ops->write(sp->tty, &sp->led_state, 1);
		sp->tx_enable = 1;
		actual = sp->tty->ops->write(sp->tty, sp->xbuff, sp->status2);
		sp->xleft -= actual;
		sp->xhead += actual;
		sp->led_state = 0x60;
		sp->tty->ops->write(sp->tty, &sp->led_state, 1);
		sp->status2 = 0;
	} else
		mod_timer(&sp->tx_t, jiffies + ((when + 1) * HZ) / 100);
}