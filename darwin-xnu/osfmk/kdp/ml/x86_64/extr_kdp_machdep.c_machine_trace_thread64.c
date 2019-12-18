#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int rip; int rsp; } ;
struct TYPE_11__ {int rbp; TYPE_2__ isf; } ;
typedef  TYPE_3__ x86_saved_state64_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int uint64_t ;
typedef  int uint32_t ;
typedef  TYPE_4__* thread_t ;
typedef  scalar_t__ boolean_t ;
typedef  int addr64_t ;
struct TYPE_13__ {int k_rbp; int k_rip; } ;
struct TYPE_12__ {int /*<<< orphan*/  kernel_stack; TYPE_1__* task; } ;
struct TYPE_9__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int MIN (int,int) ; 
 int RETURN_OFFSET64 ; 
 TYPE_8__* STACK_IKS (int /*<<< orphan*/ ) ; 
 TYPE_3__* USER_REGS64 (TYPE_4__*) ; 
 int VM_KERNEL_UNSLIDE (int) ; 
 int /*<<< orphan*/  VM_MAP_NULL ; 
 int kThreadTruncatedBT ; 
 int /*<<< orphan*/  kernel_map ; 
 int /*<<< orphan*/  machine_trace_thread_clear_validation_cache () ; 
 scalar_t__ machine_trace_thread_get_kva (int,int /*<<< orphan*/ ,int*) ; 

int
machine_trace_thread64(thread_t thread,
                       char * tracepos,
                       char * tracebound,
                       int nframes,
                       boolean_t user_p,
                       boolean_t trace_fp,
                       uint32_t * thread_trace_flags,
                       uint64_t *sp)
{
	uint64_t * tracebuf = (uint64_t *)tracepos;
	unsigned framesize  = (trace_fp ? 2 : 1) * sizeof(addr64_t);

	uint32_t fence             = 0;
	addr64_t stackptr          = 0;
	int framecount             = 0;
	addr64_t prev_rip          = 0;
	addr64_t prevsp            = 0;
	vm_offset_t kern_virt_addr = 0;
	vm_map_t bt_vm_map         = VM_MAP_NULL;

	nframes = (tracebound > tracepos) ? MIN(nframes, (int)((tracebound - tracepos) / framesize)) : 0;

	if (user_p) {
		x86_saved_state64_t	*iss64;
		iss64 = USER_REGS64(thread);
		prev_rip = iss64->isf.rip;
		stackptr = iss64->rbp;
		bt_vm_map = thread->task->map;
        if (sp && user_p) {
            *sp = iss64->isf.rsp;
        }
	}
	else {
		stackptr = STACK_IKS(thread->kernel_stack)->k_rbp;
		prev_rip = STACK_IKS(thread->kernel_stack)->k_rip;
		prev_rip = VM_KERNEL_UNSLIDE(prev_rip);
		bt_vm_map = kernel_map;
	}

	for (framecount = 0; framecount < nframes; framecount++) {

		*tracebuf++ = prev_rip;
		if (trace_fp) {
			*tracebuf++ = stackptr;
		}

		if (!stackptr || (stackptr == fence)) {
			break;
		}
		if (stackptr & 0x0000007) {
			break;
		}
		if (stackptr <= prevsp) {
			break;
		}

		kern_virt_addr = machine_trace_thread_get_kva(stackptr + RETURN_OFFSET64, bt_vm_map, thread_trace_flags);
		if (!kern_virt_addr) {
			if (thread_trace_flags) {
				*thread_trace_flags |= kThreadTruncatedBT;
			}
			break;
		}

		prev_rip = *(uint64_t *)kern_virt_addr;
		if (!user_p) {
			prev_rip = VM_KERNEL_UNSLIDE(prev_rip);
		}

		prevsp = stackptr;

		kern_virt_addr = machine_trace_thread_get_kva(stackptr, bt_vm_map, thread_trace_flags);

		if (kern_virt_addr) {
			stackptr = *(uint64_t *)kern_virt_addr;
		} else {
			stackptr = 0;
			if (thread_trace_flags) {
				*thread_trace_flags |= kThreadTruncatedBT;
			}
		}
	}

	machine_trace_thread_clear_validation_cache();

	return (uint32_t) (((char *) tracebuf) - tracepos);
}