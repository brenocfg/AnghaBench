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
struct kvm_event {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_event_count (struct kvm_event*,int) ; 

__attribute__((used)) static bool event_is_valid(struct kvm_event *event, int vcpu)
{
	return !!get_event_count(event, vcpu);
}