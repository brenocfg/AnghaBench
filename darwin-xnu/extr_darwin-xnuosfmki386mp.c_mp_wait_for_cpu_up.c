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
struct TYPE_2__ {scalar_t__ cpu_running; } ;

/* Variables and functions */
 TYPE_1__* cpu_datap (int) ; 
 int /*<<< orphan*/  delay (unsigned int) ; 

__attribute__((used)) static void
mp_wait_for_cpu_up(int slot_num, unsigned int iters, unsigned int usecdelay)
{
	while (iters-- > 0) {
		if (cpu_datap(slot_num)->cpu_running)
			break;
		delay(usecdelay);
	}
}