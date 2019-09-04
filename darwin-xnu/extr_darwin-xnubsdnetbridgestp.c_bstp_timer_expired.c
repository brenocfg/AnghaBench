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
struct bstp_timer {scalar_t__ active; scalar_t__ value; scalar_t__ latched; } ;

/* Variables and functions */
 scalar_t__ BSTP_TICK_VAL ; 
 int /*<<< orphan*/  bstp_timer_stop (struct bstp_timer*) ; 

__attribute__((used)) static int
bstp_timer_expired(struct bstp_timer *t)
{
	if (t->active == 0 || t->latched)
		return (0);
	t->value -= BSTP_TICK_VAL;
	if (t->value <= 0) {
		bstp_timer_stop(t);
		return (1);
	}
	return (0);
}