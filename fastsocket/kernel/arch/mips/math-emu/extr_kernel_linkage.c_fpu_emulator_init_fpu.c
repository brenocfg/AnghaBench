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
struct TYPE_4__ {int /*<<< orphan*/ * fpr; scalar_t__ fcr31; } ;
struct TYPE_5__ {TYPE_1__ fpu; } ;
struct TYPE_6__ {TYPE_2__ thread; } ;

/* Variables and functions */
 int /*<<< orphan*/  SIGNALLING_NAN ; 
 TYPE_3__* current ; 
 int /*<<< orphan*/  printk (char*) ; 

void fpu_emulator_init_fpu(void)
{
	static int first = 1;
	int i;

	if (first) {
		first = 0;
		printk("Algorithmics/MIPS FPU Emulator v1.5\n");
	}

	current->thread.fpu.fcr31 = 0;
	for (i = 0; i < 32; i++) {
		current->thread.fpu.fpr[i] = SIGNALLING_NAN;
	}
}