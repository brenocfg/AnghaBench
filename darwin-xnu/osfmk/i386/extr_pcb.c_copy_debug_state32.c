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
struct TYPE_4__ {int /*<<< orphan*/  dr7; int /*<<< orphan*/  dr6; int /*<<< orphan*/  dr3; int /*<<< orphan*/  dr2; int /*<<< orphan*/  dr1; int /*<<< orphan*/  dr0; int /*<<< orphan*/  dr5; int /*<<< orphan*/  dr4; } ;
typedef  TYPE_1__ x86_debug_state32_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */

void
copy_debug_state32(
		x86_debug_state32_t *src,
		x86_debug_state32_t *target,
		boolean_t all)
{
	if (all) {
		target->dr4 = src->dr4;
		target->dr5 = src->dr5;
	}

	target->dr0 = src->dr0;
	target->dr1 = src->dr1;
	target->dr2 = src->dr2;
	target->dr3 = src->dr3;
	target->dr6 = src->dr6;
	target->dr7 = src->dr7;
}