#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ PAB_active; } ;
typedef  TYPE_1__ cpu_data_t ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  do_print_all_backtraces (char const*) ; 
 TYPE_1__* getCpuDatap () ; 
 unsigned int not_in_kdp ; 

__attribute__((used)) static void
print_all_backtraces(const char	*message)
{
	unsigned int initial_not_in_kdp = not_in_kdp;

	cpu_data_t * cpu_data_ptr = getCpuDatap();

	assert(cpu_data_ptr->PAB_active == FALSE);
	cpu_data_ptr->PAB_active = TRUE;

	/*
	 * Because print all backtraces uses the pmap routines, it needs to
	 * avoid taking pmap locks.  Right now, this is conditionalized on
	 * not_in_kdp.
	 */
	not_in_kdp = 0;
	do_print_all_backtraces(message);

	not_in_kdp = initial_not_in_kdp;

	cpu_data_ptr->PAB_active = FALSE;
}