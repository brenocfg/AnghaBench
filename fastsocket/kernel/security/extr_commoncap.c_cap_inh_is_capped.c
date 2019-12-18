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
 int /*<<< orphan*/  SECURITY_CAP_AUDIT ; 
 scalar_t__ cap_capable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  current_cred () ; 

__attribute__((used)) static inline int cap_inh_is_capped(void)
{
#ifdef CONFIG_SECURITY_FILE_CAPABILITIES

	/* they are so limited unless the current task has the CAP_SETPCAP
	 * capability
	 */
	if (cap_capable(current, current_cred(), CAP_SETPCAP,
			SECURITY_CAP_AUDIT) == 0)
		return 0;
#endif
	return 1;
}