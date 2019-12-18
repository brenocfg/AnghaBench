#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct timer_list {int dummy; } ;
struct TYPE_3__ {unsigned char state; struct timer_list timer; } ;
struct TYPE_4__ {TYPE_1__ scir; } ;

/* Variables and functions */
 unsigned char SCIR_CPU_ACTIVITY ; 
 scalar_t__ SCIR_CPU_HB_INTERVAL ; 
 unsigned char SCIR_CPU_HEARTBEAT ; 
 scalar_t__ idle_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer_pinned (struct timer_list*,scalar_t__) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 TYPE_2__* uv_hub_info ; 
 int /*<<< orphan*/  uv_set_scir_bits (unsigned char) ; 

__attribute__((used)) static void uv_heartbeat(unsigned long ignored)
{
	struct timer_list *timer = &uv_hub_info->scir.timer;
	unsigned char bits = uv_hub_info->scir.state;

	/* flip heartbeat bit */
	bits ^= SCIR_CPU_HEARTBEAT;

	/* is this cpu idle? */
	if (idle_cpu(raw_smp_processor_id()))
		bits &= ~SCIR_CPU_ACTIVITY;
	else
		bits |= SCIR_CPU_ACTIVITY;

	/* update system controller interface reg */
	uv_set_scir_bits(bits);

	/* enable next timer period */
	mod_timer_pinned(timer, jiffies + SCIR_CPU_HB_INTERVAL);
}