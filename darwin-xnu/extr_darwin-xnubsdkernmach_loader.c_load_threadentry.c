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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  thread_state_t ;
typedef  int /*<<< orphan*/  mach_vm_offset_t ;
typedef  int /*<<< orphan*/  load_return_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  LOAD_BADMACHO ; 
 int /*<<< orphan*/  LOAD_FAILURE ; 
 int /*<<< orphan*/  LOAD_SUCCESS ; 
 int /*<<< orphan*/  MACH_VM_MIN_ADDRESS ; 
 int UINT32_MAX ; 
 scalar_t__ thread_entrypoint (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
load_return_t
load_threadentry(
	thread_t	thread,
	uint32_t	*ts,
	uint32_t	total_size,
	mach_vm_offset_t	*entry_point
)
{
	kern_return_t	ret;
	uint32_t	size;
	int		flavor;
	uint32_t	entry_size;

	/*
	 *	Set the thread state.
	 */
	*entry_point = MACH_VM_MIN_ADDRESS;
	while (total_size > 0) {
		flavor = *ts++;
		size = *ts++;
		if (UINT32_MAX-2 < size ||
		    UINT32_MAX/sizeof(uint32_t) < size+2)
			return (LOAD_BADMACHO);
		entry_size = (size+2)*sizeof(uint32_t);
		if (entry_size > total_size)
			return(LOAD_BADMACHO);
		total_size -= entry_size;
		/*
		 * Third argument is a kernel space pointer; it gets cast
		 * to the appropriate type in thread_entrypoint() based on
		 * the value of flavor.
		 */
		ret = thread_entrypoint(thread, flavor, (thread_state_t)ts, size, entry_point);
		if (ret != KERN_SUCCESS) {
			return(LOAD_FAILURE);
		}
		ts += size;	/* ts is a (uint32_t *) */
	}
	return(LOAD_SUCCESS);
}