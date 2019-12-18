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
struct TYPE_3__ {int /*<<< orphan*/  readb_func; } ;
typedef  TYPE_1__ Q68State ;
typedef  int /*<<< orphan*/  Q68ReadFunc ;

/* Variables and functions */

void q68_set_readb_func(Q68State *state, Q68ReadFunc func)
{
    state->readb_func = func;
}