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
 scalar_t__ vm_page_free_count ; 
 scalar_t__ vm_page_free_reserved ; 

int
vm_pool_low(void)
{
	/* No locking, at worst we will fib. */
	return( vm_page_free_count <= vm_page_free_reserved );
}