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
struct TYPE_2__ {int /*<<< orphan*/  thr; } ;

/* Variables and functions */
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  udbg_550_flush () ; 
 TYPE_1__* udbg_comport ; 

__attribute__((used)) static void udbg_550_putc(char c)
{
	if (udbg_comport) {
		if (c == '\n')
			udbg_550_putc('\r');
		udbg_550_flush();
		out_8(&udbg_comport->thr, c);
	}
}