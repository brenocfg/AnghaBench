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
typedef  int uint64_t ;
typedef  scalar_t__ volatile uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  MAIN_CNT; } ;
typedef  TYPE_1__ hpetReg_t ;

/* Variables and functions */
 scalar_t__ hpetArea ; 

uint64_t
rdHPET(void)
{
	hpetReg_t		*hpetp = (hpetReg_t *) hpetArea;
	volatile uint32_t	*regp = (uint32_t *) &hpetp->MAIN_CNT;
	uint32_t		high;
	uint32_t		low;

	do {
		high = *(regp + 1);
		low = *regp;
	} while (high != *(regp + 1));

	return (((uint64_t) high) << 32) | low;
}