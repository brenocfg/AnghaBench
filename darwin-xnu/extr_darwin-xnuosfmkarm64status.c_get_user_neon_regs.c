#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* thread_t ;
typedef  int /*<<< orphan*/  arm_neon_saved_state_t ;
struct TYPE_4__ {int /*<<< orphan*/ * uNeon; } ;
struct TYPE_5__ {TYPE_1__ machine; } ;

/* Variables and functions */

arm_neon_saved_state_t *
get_user_neon_regs(
	      thread_t thread)
{
	return (thread->machine.uNeon);
}