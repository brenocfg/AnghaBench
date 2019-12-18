#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct bstp_timer {int active; scalar_t__ latched; int /*<<< orphan*/  value; } ;

/* Variables and functions */

__attribute__((used)) static void
bstp_timer_start(struct bstp_timer *t, uint16_t v)
{
	t->value = v;
	t->active = 1;
	t->latched = 0;
}