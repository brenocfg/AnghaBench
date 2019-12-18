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
typedef  int /*<<< orphan*/  ulong ;
typedef  int u32 ;
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct mpsc_port_info {int MPSC_CHR_1_m; TYPE_1__ port; scalar_t__ mpsc_base; scalar_t__ mirror_regs; } ;

/* Variables and functions */
 scalar_t__ MPSC_CHR_1 ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mpsc_break_ctl(struct uart_port *port, int ctl)
{
	struct mpsc_port_info *pi = (struct mpsc_port_info *)port;
	ulong	flags;
	u32	v;

	v = ctl ? 0x00ff0000 : 0;

	spin_lock_irqsave(&pi->port.lock, flags);
	if (pi->mirror_regs)
		pi->MPSC_CHR_1_m = v;
	writel(v, pi->mpsc_base + MPSC_CHR_1);
	spin_unlock_irqrestore(&pi->port.lock, flags);
}