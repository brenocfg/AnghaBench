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
struct TYPE_2__ {int (* rd0 ) () ;int /*<<< orphan*/  (* rr0 ) () ;} ;

/* Variables and functions */
 TYPE_1__* gPESF ; 
 int /*<<< orphan*/  stub1 () ; 
 int stub2 () ; 
 scalar_t__ uart_initted ; 

int
uart_getc(void)
{				/* returns -1 if no data available */
	if (uart_initted) {
		if (!gPESF->rr0())
			return -1;	/* Receive data read */
		return gPESF->rd0();
	}
	return -1;
}