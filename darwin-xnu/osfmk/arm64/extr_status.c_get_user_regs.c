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
struct arm_saved_state {int dummy; } ;
struct TYPE_4__ {struct arm_saved_state* upcb; } ;
struct TYPE_5__ {TYPE_1__ machine; } ;

/* Variables and functions */

struct arm_saved_state *
get_user_regs(
	      thread_t thread)
{
	return (thread->machine.upcb);
}