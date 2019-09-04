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
typedef  int /*<<< orphan*/  nstat_src_ref_t ;
struct TYPE_3__ {int /*<<< orphan*/  ncs_next_srcref; } ;
typedef  TYPE_1__ nstat_control_state ;

/* Variables and functions */

__attribute__((used)) static nstat_src_ref_t
nstat_control_next_src_ref(
	nstat_control_state	*state)
{
	return ++state->ncs_next_srcref;
}