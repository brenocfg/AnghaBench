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

/* Variables and functions */
 int /*<<< orphan*/  CAP_SETPCAP ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int cap_limit_ptraced_target(void)
{
#ifndef CONFIG_SECURITY_FILE_CAPABILITIES
	if (capable(CAP_SETPCAP))
		return 0;
#endif
	return 1;
}