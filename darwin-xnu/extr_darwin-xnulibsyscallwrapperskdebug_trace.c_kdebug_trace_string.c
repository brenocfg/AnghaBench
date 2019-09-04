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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 scalar_t__ __kdebug_trace_string (int /*<<< orphan*/ ,scalar_t__,char const*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  kdebug_is_enabled (int /*<<< orphan*/ ) ; 

uint64_t
kdebug_trace_string(uint32_t debugid, uint64_t str_id, const char *str)
{
	if (!kdebug_is_enabled(debugid)) {
		return 0;
	}

	if ((int64_t)str_id == -1) {
		errno = EINVAL;
		return (uint64_t)-1;
	}

	if (str_id == 0 && str == NULL) {
		errno = EINVAL;
		return (uint64_t)-1;
	}

	return __kdebug_trace_string(debugid, str_id, str);
}