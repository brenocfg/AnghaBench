#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_4__ {int* int_mask; int int_enable; int* cnt_ovf; } ;
struct TYPE_3__ {int /*<<< orphan*/  ovf; } ;

/* Variables and functions */
 int CCNT ; 
 int PMN3 ; 
 int PMU_ENABLE ; 
 TYPE_2__* pmu ; 
 int read_pmnc () ; 
 TYPE_1__* results ; 
 int /*<<< orphan*/  write_pmnc (int) ; 

__attribute__((used)) static void inline __xsc2_check_ctrs(void)
{
	int i;
	u32 flag = 0, pmnc = read_pmnc();

	pmnc &= ~PMU_ENABLE;
	write_pmnc(pmnc);

	/* read overflow flag register */
	__asm__ __volatile__ ("mrc p14, 0, %0, c5, c1, 0" : "=r" (flag));

	for (i = CCNT; i <= PMN3; i++) {
		if (!(pmu->int_mask[i] & pmu->int_enable))
			continue;

		if (flag & pmu->cnt_ovf[i])
			results[i].ovf++;
	}

	/* writeback clears overflow bits */
	__asm__ __volatile__ ("mcr p14, 0, %0, c5, c1, 0" : : "r" (flag));
}