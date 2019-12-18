#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  scalar_t__ thread_t ;
struct thread_command {int cmdsize; } ;
typedef  void* mach_vm_offset_t ;
typedef  scalar_t__ load_return_t ;
struct TYPE_5__ {scalar_t__ thread_count; int /*<<< orphan*/  unixproc; void* entry_point; scalar_t__ using_lcmain; void* user_stack; int /*<<< orphan*/  user_stack_alloc_size; } ;
typedef  TYPE_1__ load_result_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 scalar_t__ LOAD_BADMACHO ; 
 scalar_t__ LOAD_FAILURE ; 
 scalar_t__ LOAD_SUCCESS ; 
 void* MACH_VM_MIN_ADDRESS ; 
 int /*<<< orphan*/  MAXSSIZ ; 
 scalar_t__ THREAD_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ load_threadentry (scalar_t__,int /*<<< orphan*/ *,int,void**) ; 
 scalar_t__ load_threadstack (scalar_t__,int /*<<< orphan*/ *,int,void**,int*,TYPE_1__*) ; 
 scalar_t__ load_threadstate (scalar_t__,int /*<<< orphan*/ *,int,TYPE_1__*) ; 

__attribute__((used)) static
load_return_t
load_unixthread(
	struct thread_command	*tcp,
	thread_t		thread,
	int64_t				slide,
	load_result_t		*result
)
{
	load_return_t	ret;
	int customstack =0;
	mach_vm_offset_t addr;
	if (tcp->cmdsize < sizeof(*tcp))
		return (LOAD_BADMACHO);
	if (result->thread_count != 0) {
		return (LOAD_FAILURE);
	}

	if (thread == THREAD_NULL)
		return (LOAD_SUCCESS);
	
	ret = load_threadstack(thread,
				(uint32_t *)(((vm_offset_t)tcp) +
					sizeof(struct thread_command)),
				tcp->cmdsize - sizeof(struct thread_command),
				&addr, &customstack, result);
	if (ret != LOAD_SUCCESS)
		return(ret);

	/* LC_UNIXTHREAD optionally specifies stack size and location */

	if (!customstack) {
		result->user_stack_alloc_size = MAXSSIZ;
	}

	/* The stack slides down from the default location */
	result->user_stack = addr;
	result->user_stack -= slide;

	ret = load_threadentry(thread,
				(uint32_t *)(((vm_offset_t)tcp) +
					sizeof(struct thread_command)),
				tcp->cmdsize - sizeof(struct thread_command),
				&addr);
	if (ret != LOAD_SUCCESS)
		return(ret);

	if (result->using_lcmain || result->entry_point != MACH_VM_MIN_ADDRESS) {
		/* Already processed LC_MAIN or LC_UNIXTHREAD */
		return (LOAD_FAILURE);
	}

	result->entry_point = addr;
	result->entry_point += slide;

	ret = load_threadstate(thread,
				(uint32_t *)(((vm_offset_t)tcp) + sizeof(struct thread_command)),
				tcp->cmdsize - sizeof(struct thread_command),
				result);
	if (ret != LOAD_SUCCESS)
		return (ret);

	result->unixproc = TRUE;
	result->thread_count++;

	return(LOAD_SUCCESS);
}