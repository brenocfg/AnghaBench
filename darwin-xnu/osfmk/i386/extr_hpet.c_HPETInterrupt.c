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
struct TYPE_2__ {int /*<<< orphan*/  HpetInt; } ;

/* Variables and functions */
 int /*<<< orphan*/  pmHPETInterrupt () ; 
 TYPE_1__* x86_package () ; 

int
HPETInterrupt(void)
{

	/* All we do here is to bump the count */
	x86_package()->HpetInt++;

	/*
	 * Let power management do it's thing.
	 */
	pmHPETInterrupt();

	/* Return and show that the 'rupt has been handled... */
	return 1;
}