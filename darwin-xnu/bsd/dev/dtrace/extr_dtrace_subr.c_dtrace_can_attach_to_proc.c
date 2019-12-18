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
typedef  int /*<<< orphan*/  proc_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ cs_restricted (int /*<<< orphan*/ *) ; 

boolean_t
dtrace_can_attach_to_proc(proc_t *proc)
{
#pragma unused(proc)
	ASSERT(proc != NULL);

#if CONFIG_CSR
	if (cs_restricted(proc))
		return FALSE;
#endif

	return TRUE;
}