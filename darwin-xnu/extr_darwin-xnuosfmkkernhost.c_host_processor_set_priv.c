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
typedef  scalar_t__ processor_set_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
typedef  scalar_t__ host_priv_t ;

/* Variables and functions */
 scalar_t__ HOST_PRIV_NULL ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ PROCESSOR_SET_NULL ; 

kern_return_t
host_processor_set_priv(host_priv_t host_priv, processor_set_t pset_name, processor_set_t * pset)
{
	if (host_priv == HOST_PRIV_NULL || pset_name == PROCESSOR_SET_NULL) {
		*pset = PROCESSOR_SET_NULL;

		return (KERN_INVALID_ARGUMENT);
	}

	*pset = pset_name;

	return (KERN_SUCCESS);
}