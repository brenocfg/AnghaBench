#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  process; } ;
typedef  TYPE_1__ EQContext ;

/* Variables and functions */
 scalar_t__ ARCH_X86 ; 
 int /*<<< orphan*/  ff_eq_init_x86 (TYPE_1__*) ; 
 int /*<<< orphan*/  process_c ; 

void ff_eq_init(EQContext *eq)
{
    eq->process = process_c;
    if (ARCH_X86)
        ff_eq_init_x86(eq);
}