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
 int AVAILABLE_NON_COMPRESSED_MEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VM_PAGE_Q_BACKING_UP (int /*<<< orphan*/ *) ; 
 int vm_page_pageable_external_count ; 
 int /*<<< orphan*/  vm_pageout_queue_external ; 

boolean_t
must_throttle_writes()
{
	if (VM_PAGE_Q_BACKING_UP(&vm_pageout_queue_external) &&
	    vm_page_pageable_external_count > (AVAILABLE_NON_COMPRESSED_MEMORY * 6) / 10)
		return (TRUE);

	return (FALSE);
}