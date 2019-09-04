#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* processor_t ;
typedef  int /*<<< orphan*/ * processor_set_t ;
typedef  int /*<<< orphan*/  kern_return_t ;
struct TYPE_4__ {int state; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_FAILURE ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 TYPE_1__* PROCESSOR_NULL ; 
 int PROCESSOR_OFF_LINE ; 
 int PROCESSOR_SHUTDOWN ; 
 int /*<<< orphan*/  pset0 ; 

kern_return_t
processor_get_assignment(
	processor_t	processor,
	processor_set_t	*pset)
{
	int state;

	if (processor == PROCESSOR_NULL)
		return(KERN_INVALID_ARGUMENT);

	state = processor->state;
	if (state == PROCESSOR_SHUTDOWN || state == PROCESSOR_OFF_LINE)
		return(KERN_FAILURE);

	*pset = &pset0;

	return(KERN_SUCCESS);
}