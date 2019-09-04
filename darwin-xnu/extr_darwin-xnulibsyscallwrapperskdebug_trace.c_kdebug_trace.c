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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;

/* Variables and functions */
 int __kdebug_trace64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kdebug_is_enabled (int /*<<< orphan*/ ) ; 

int
kdebug_trace(uint32_t debugid, uint64_t arg1, uint64_t arg2, uint64_t arg3,
             uint64_t arg4)
{
	if (!kdebug_is_enabled(debugid)) {
		return 0;
	}

	return __kdebug_trace64(debugid, arg1, arg2, arg3, arg4);
}