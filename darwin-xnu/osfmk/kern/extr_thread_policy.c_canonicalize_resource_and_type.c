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
typedef  int /*<<< orphan*/  user_addr_t ;

/* Variables and functions */
 scalar_t__ QOS_OVERRIDE_MODE_FINE_GRAINED_OVERRIDE ; 
 scalar_t__ QOS_OVERRIDE_MODE_FINE_GRAINED_OVERRIDE_BUT_SINGLE_MUTEX_OVERRIDE ; 
 scalar_t__ QOS_OVERRIDE_MODE_IGNORE_OVERRIDE ; 
 scalar_t__ QOS_OVERRIDE_MODE_OVERHANG_PEAK ; 
 int THREAD_QOS_OVERRIDE_TYPE_PTHREAD_MUTEX ; 
 int THREAD_QOS_OVERRIDE_TYPE_UNKNOWN ; 
 int /*<<< orphan*/  USER_ADDR_NULL ; 
 scalar_t__ qos_override_mode ; 

__attribute__((used)) static void canonicalize_resource_and_type(user_addr_t *resource, int *resource_type) {
	if (qos_override_mode == QOS_OVERRIDE_MODE_OVERHANG_PEAK || qos_override_mode == QOS_OVERRIDE_MODE_IGNORE_OVERRIDE) {
		/* Map all input resource/type to a single one */
		*resource = USER_ADDR_NULL;
		*resource_type = THREAD_QOS_OVERRIDE_TYPE_UNKNOWN;
	} else if (qos_override_mode == QOS_OVERRIDE_MODE_FINE_GRAINED_OVERRIDE) {
		/* no transform */
	} else if (qos_override_mode == QOS_OVERRIDE_MODE_FINE_GRAINED_OVERRIDE_BUT_SINGLE_MUTEX_OVERRIDE) {
		/* Map all mutex overrides to a single one, to avoid memory overhead */
		if (*resource_type == THREAD_QOS_OVERRIDE_TYPE_PTHREAD_MUTEX) {
			*resource = USER_ADDR_NULL;
		}
	}
}