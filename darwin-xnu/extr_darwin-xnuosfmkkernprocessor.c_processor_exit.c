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
typedef  scalar_t__ processor_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 scalar_t__ PROCESSOR_NULL ; 
 int /*<<< orphan*/  processor_shutdown (scalar_t__) ; 

kern_return_t
processor_exit(
	processor_t	processor)
{
	if (processor == PROCESSOR_NULL)
		return(KERN_INVALID_ARGUMENT);

	return(processor_shutdown(processor));
}