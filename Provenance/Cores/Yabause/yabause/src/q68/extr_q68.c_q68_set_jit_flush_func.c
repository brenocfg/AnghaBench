#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void (* jit_flush ) () ;} ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */

void q68_set_jit_flush_func(Q68State *state, void (*flush_func)(void))
{
    state->jit_flush   = flush_func;
}