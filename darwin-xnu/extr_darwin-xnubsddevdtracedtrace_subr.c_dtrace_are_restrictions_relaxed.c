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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 

boolean_t
dtrace_are_restrictions_relaxed(void)
{
#if CONFIG_CSR
	if (csr_check(CSR_ALLOW_APPLE_INTERNAL) == 0)
		return TRUE;
#endif

	return FALSE;
}