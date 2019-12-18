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
struct TYPE_2__ {int /*<<< orphan*/  (* td0 ) (char) ;int /*<<< orphan*/  (* tr0 ) () ;} ;

/* Variables and functions */
 TYPE_1__* gPESF ; 
 int /*<<< orphan*/  stub1 () ; 
 int /*<<< orphan*/  stub2 (char) ; 
 scalar_t__ uart_initted ; 

void
uart_putc(char c)
{
	if (uart_initted) {
		while (!gPESF->tr0());	/* Wait until THR is empty. */
		gPESF->td0(c);
	}
}