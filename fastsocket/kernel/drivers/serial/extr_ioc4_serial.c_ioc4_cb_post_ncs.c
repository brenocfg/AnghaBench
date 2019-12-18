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
struct uart_icount {int /*<<< orphan*/  parity; int /*<<< orphan*/  overrun; int /*<<< orphan*/  frame; int /*<<< orphan*/  brk; } ;
struct uart_port {struct uart_icount icount; } ;

/* Variables and functions */
 int NCS_BREAK ; 
 int NCS_FRAMING ; 
 int NCS_OVERRUN ; 
 int NCS_PARITY ; 

__attribute__((used)) static void ioc4_cb_post_ncs(struct uart_port *the_port, int ncs)
{
	struct uart_icount *icount;

	icount = &the_port->icount;

	if (ncs & NCS_BREAK)
		icount->brk++;
	if (ncs & NCS_FRAMING)
		icount->frame++;
	if (ncs & NCS_OVERRUN)
		icount->overrun++;
	if (ncs & NCS_PARITY)
		icount->parity++;
}