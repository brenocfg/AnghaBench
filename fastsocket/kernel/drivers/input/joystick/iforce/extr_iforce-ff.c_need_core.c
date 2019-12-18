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
struct TYPE_3__ {scalar_t__ length; scalar_t__ delay; } ;
struct TYPE_4__ {scalar_t__ button; scalar_t__ interval; } ;
struct ff_effect {scalar_t__ direction; TYPE_1__ replay; TYPE_2__ trigger; } ;

/* Variables and functions */

__attribute__((used)) static int need_core(struct ff_effect *old, struct ff_effect *new)
{
	if (old->direction != new->direction
		|| old->trigger.button != new->trigger.button
		|| old->trigger.interval != new->trigger.interval
		|| old->replay.length != new->replay.length
		|| old->replay.delay != new->replay.delay)
		return 1;

	return 0;
}