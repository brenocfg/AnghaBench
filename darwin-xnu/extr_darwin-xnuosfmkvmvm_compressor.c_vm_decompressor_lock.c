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
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PAGE_REPLACEMENT_ALLOWED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  decompressions_blocked ; 

void
vm_decompressor_lock(void)
{
	PAGE_REPLACEMENT_ALLOWED(TRUE);

	decompressions_blocked = TRUE;
	
	PAGE_REPLACEMENT_ALLOWED(FALSE);
}