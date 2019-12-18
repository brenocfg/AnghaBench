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
struct kvm_kpit_channel_state {int /*<<< orphan*/  count_load_time; } ;
struct kvm {int dummy; } ;
typedef  int /*<<< orphan*/  s64 ;

/* Variables and functions */
 int /*<<< orphan*/  __kpit_elapsed (struct kvm*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_to_ns (int /*<<< orphan*/ ) ; 

__attribute__((used)) static s64 kpit_elapsed(struct kvm *kvm, struct kvm_kpit_channel_state *c,
			int channel)
{
	if (channel == 0)
		return __kpit_elapsed(kvm);

	return ktime_to_ns(ktime_sub(ktime_get(), c->count_load_time));
}