#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ user_addr_t ;
typedef  TYPE_1__* thread_t ;
struct thread_qos_override {scalar_t__ override_resource; int override_resource_type; scalar_t__ override_contended_resource_count; struct thread_qos_override* override_next; } ;
typedef  scalar_t__ boolean_t ;
struct TYPE_3__ {struct thread_qos_override* overrides; } ;

/* Variables and functions */
 scalar_t__ THREAD_QOS_OVERRIDE_RESOURCE_WILDCARD ; 
 int THREAD_QOS_OVERRIDE_TYPE_WILDCARD ; 

__attribute__((used)) static void
find_and_decrement_qos_override(thread_t       thread,
                                user_addr_t    resource,
                                int            resource_type,
                                boolean_t      reset,
                                struct thread_qos_override **free_override_list)
{
	struct thread_qos_override *override, *override_prev;

	override_prev = NULL;
	override = thread->overrides;
	while (override) {
		struct thread_qos_override *override_next = override->override_next;

		if ((THREAD_QOS_OVERRIDE_RESOURCE_WILDCARD == resource  || override->override_resource == resource) &&
		    (THREAD_QOS_OVERRIDE_TYPE_WILDCARD == resource_type || override->override_resource_type == resource_type)) {

			if (reset) {
				override->override_contended_resource_count = 0;
			} else {
				override->override_contended_resource_count--;
			}

			if (override->override_contended_resource_count == 0) {
				if (override_prev == NULL) {
					thread->overrides = override_next;
				} else {
					override_prev->override_next = override_next;
				}

				/* Add to out-param for later zfree */
				override->override_next = *free_override_list;
				*free_override_list = override;
			} else {
				override_prev = override;
			}

			if (THREAD_QOS_OVERRIDE_RESOURCE_WILDCARD != resource) {
				return;
			}
		} else {
			override_prev = override;
		}

		override = override_next;
	}
}