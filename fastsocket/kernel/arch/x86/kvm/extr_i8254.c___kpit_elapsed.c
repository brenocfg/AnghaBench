#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ period; int /*<<< orphan*/  timer; } ;
struct kvm_kpit_state {TYPE_3__ pit_timer; } ;
struct TYPE_5__ {TYPE_1__* vpit; } ;
struct kvm {TYPE_2__ arch; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;
struct TYPE_4__ {struct kvm_kpit_state pit_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  hrtimer_get_remaining (int /*<<< orphan*/ *) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ mod_64 (scalar_t__,scalar_t__) ; 

__attribute__((used)) static s64 __kpit_elapsed(struct kvm *kvm)
{
	s64 elapsed;
	ktime_t remaining;
	struct kvm_kpit_state *ps = &kvm->arch.vpit->pit_state;

	if (!ps->pit_timer.period)
		return 0;

	/*
	 * The Counter does not stop when it reaches zero. In
	 * Modes 0, 1, 4, and 5 the Counter ``wraps around'' to
	 * the highest count, either FFFF hex for binary counting
	 * or 9999 for BCD counting, and continues counting.
	 * Modes 2 and 3 are periodic; the Counter reloads
	 * itself with the initial count and continues counting
	 * from there.
	 */
	remaining = hrtimer_get_remaining(&ps->pit_timer.timer);
	elapsed = ps->pit_timer.period - ktime_to_ns(remaining);
	elapsed = mod_64(elapsed, ps->pit_timer.period);

	return elapsed;
}