#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int eip; int ebp; } ;
typedef  TYPE_2__ x86_saved_state32_t ;
typedef  scalar_t__ vm_offset_t ;
typedef  int /*<<< orphan*/  vm_map_t ;
typedef  int uint32_t ;
typedef  TYPE_3__* thread_t ;
typedef  scalar_t__ boolean_t ;
struct TYPE_9__ {TYPE_1__* task; } ;
struct TYPE_7__ {int /*<<< orphan*/  map; } ;

/* Variables and functions */
 int MIN (int,int) ; 
 int RETURN_OFFSET ; 
 TYPE_2__* USER_REGS32 (TYPE_3__*) ; 
 int /*<<< orphan*/  VM_MAP_NULL ; 
 int kThreadTruncatedBT ; 
 int /*<<< orphan*/  machine_trace_thread_clear_validation_cache () ; 
 scalar_t__ machine_trace_thread_get_kva (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
machine_trace_thread(thread_t thread,
                     char * tracepos,
                     char * tracebound,
                     int nframes,
                     boolean_t user_p,
                     boolean_t trace_fp,
                     uint32_t * thread_trace_flags)
{
	uint32_t * tracebuf = (uint32_t *)tracepos;
	uint32_t framesize  = (trace_fp ? 2 : 1) * sizeof(uint32_t);

	uint32_t fence             = 0;
	uint32_t stackptr          = 0;
	uint32_t stacklimit        = 0xfc000000;
	int framecount             = 0;
	uint32_t prev_eip          = 0;
	uint32_t prevsp            = 0;
	vm_offset_t kern_virt_addr = 0;
	vm_map_t bt_vm_map         = VM_MAP_NULL;

	nframes = (tracebound > tracepos) ? MIN(nframes, (int)((tracebound - tracepos) / framesize)) : 0;

	if (user_p) {
		    x86_saved_state32_t	*iss32;
		
		iss32 = USER_REGS32(thread);
		prev_eip = iss32->eip;
		stackptr = iss32->ebp;

		stacklimit = 0xffffffff;
		bt_vm_map = thread->task->map;
	}
	else
		panic("32-bit trace attempted on 64-bit kernel");

	for (framecount = 0; framecount < nframes; framecount++) {

		*tracebuf++ = prev_eip;
		if (trace_fp) {
			*tracebuf++ = stackptr;
		}

		/* Invalid frame, or hit fence */
		if (!stackptr || (stackptr == fence)) {
			break;
		}

		/* Unaligned frame */
		if (stackptr & 0x0000003) {
			break;
		}
		
		if (stackptr <= prevsp) {
			break;
		}

		if (stackptr > stacklimit) {
			break;
		}

		kern_virt_addr = machine_trace_thread_get_kva(stackptr + RETURN_OFFSET, bt_vm_map, thread_trace_flags);

		if (!kern_virt_addr) {
			if (thread_trace_flags) {
				*thread_trace_flags |= kThreadTruncatedBT;
			}
			break;
		}

		prev_eip = *(uint32_t *)kern_virt_addr;
		
		prevsp = stackptr;

		kern_virt_addr = machine_trace_thread_get_kva(stackptr, bt_vm_map, thread_trace_flags);

		if (kern_virt_addr) {
			stackptr = *(uint32_t *)kern_virt_addr;
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