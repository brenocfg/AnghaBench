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
typedef  int /*<<< orphan*/ * processor_set_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ host_t ;

/* Variables and functions */
 scalar_t__ HOST_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 int /*<<< orphan*/  pset0 ; 

kern_return_t
processor_set_default(
	host_t			host,
	processor_set_t		*pset)
{
	if (host == HOST_NULL)
		return(KERN_INVALID_ARGUMENT);

	*pset = &pset0;

	return (KERN_SUCCESS);
}