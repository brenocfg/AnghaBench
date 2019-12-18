#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct uart_sunsab_port {int cached_mode; int cached_pvr; int cached_dafo; int cached_ebrg; TYPE_3__* regs; int /*<<< orphan*/  irqflags; } ;
struct TYPE_5__ {int /*<<< orphan*/  ccr2; int /*<<< orphan*/  pvr; int /*<<< orphan*/  mode; } ;
struct TYPE_4__ {int /*<<< orphan*/  bgr; int /*<<< orphan*/  dafo; } ;
struct TYPE_6__ {TYPE_2__ rw; TYPE_1__ w; } ;

/* Variables and functions */
 int /*<<< orphan*/  SAB82532_REGS_PENDING ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int readb (int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sunsab_tx_idle(struct uart_sunsab_port *up)
{
	if (test_bit(SAB82532_REGS_PENDING, &up->irqflags)) {
		u8 tmp;

		clear_bit(SAB82532_REGS_PENDING, &up->irqflags);
		writeb(up->cached_mode, &up->regs->rw.mode);
		writeb(up->cached_pvr, &up->regs->rw.pvr);
		writeb(up->cached_dafo, &up->regs->w.dafo);

		writeb(up->cached_ebrg & 0xff, &up->regs->w.bgr);
		tmp = readb(&up->regs->rw.ccr2);
		tmp &= ~0xc0;
		tmp |= (up->cached_ebrg >> 2) & 0xc0;
		writeb(tmp, &up->regs->rw.ccr2);
	}
}