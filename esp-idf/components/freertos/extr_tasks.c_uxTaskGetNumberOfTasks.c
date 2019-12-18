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
typedef  int /*<<< orphan*/  UBaseType_t ;

/* Variables and functions */
 int /*<<< orphan*/  uxCurrentNumberOfTasks ; 

UBaseType_t uxTaskGetNumberOfTasks( void )
{
	/* A critical section is not required because the variables are of type
	BaseType_t. */
	return uxCurrentNumberOfTasks;
}