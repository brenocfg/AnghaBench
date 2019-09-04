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
typedef  int /*<<< orphan*/  event_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PAGE_REPLACEMENT_ALLOWED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  decompressions_blocked ; 
 int /*<<< orphan*/  thread_wakeup (int /*<<< orphan*/ ) ; 

void
vm_decompressor_unlock(void)
{
	PAGE_REPLACEMENT_ALLOWED(TRUE);

	decompressions_blocked = FALSE;

	PAGE_REPLACEMENT_ALLOWED(FALSE);

	thread_wakeup((event_t)&decompressions_blocked);
}