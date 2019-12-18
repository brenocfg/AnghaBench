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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ host_t ;

/* Variables and functions */
 scalar_t__ HOST_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  PAGE_SIZE ; 

kern_return_t
host_page_size(host_t host, vm_size_t * out_page_size)
{
	if (host == HOST_NULL)
		return (KERN_INVALID_ARGUMENT);

	*out_page_size = PAGE_SIZE;

	return (KERN_SUCCESS);
}