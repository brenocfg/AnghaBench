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
struct TYPE_2__ {scalar_t__ handler; } ;

/* Variables and functions */
 TYPE_1__* _xt_interrupt_table ; 
 int portNUM_PROCESSORS ; 
 scalar_t__ xt_unhandled_interrupt ; 

__attribute__((used)) static bool int_has_handler(int intr, int cpu)
{
    return (_xt_interrupt_table[intr*portNUM_PROCESSORS+cpu].handler != xt_unhandled_interrupt);
}