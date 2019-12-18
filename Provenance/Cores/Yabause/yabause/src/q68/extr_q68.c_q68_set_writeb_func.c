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
struct TYPE_3__ {int /*<<< orphan*/  writeb_func; } ;
typedef  int /*<<< orphan*/  Q68WriteFunc ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */

void q68_set_writeb_func(Q68State *state, Q68WriteFunc func)
{
    state->writeb_func = func;
}