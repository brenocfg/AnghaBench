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
struct ct_timer_instance {scalar_t__ need_update; scalar_t__ running; TYPE_2__* substream; int /*<<< orphan*/  frag_count; } ;
struct TYPE_4__ {TYPE_1__* runtime; } ;
struct TYPE_3__ {int /*<<< orphan*/  period_size; } ;

/* Variables and functions */

__attribute__((used)) static void ct_xfitimer_prepare(struct ct_timer_instance *ti)
{
	ti->frag_count = ti->substream->runtime->period_size;
	ti->running = 0;
	ti->need_update = 0;
}