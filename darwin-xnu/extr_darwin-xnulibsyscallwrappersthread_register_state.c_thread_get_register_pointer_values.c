#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int __rsp; uintptr_t __rax; uintptr_t __rbx; uintptr_t __rcx; uintptr_t __rdx; uintptr_t __rdi; uintptr_t __rbp; uintptr_t __r8; uintptr_t __r9; uintptr_t __r10; uintptr_t __r11; uintptr_t __r12; uintptr_t __r13; uintptr_t __r14; uintptr_t __r15; } ;
typedef  TYPE_1__ x86_thread_state64_t ;
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  thread_state_t ;
typedef  int /*<<< orphan*/  thread_state_flavor_t ;
typedef  int /*<<< orphan*/  mach_msg_type_number_t ;
typedef  scalar_t__ kern_return_t ;

/* Variables and functions */
 scalar_t__ KERN_INSUFFICIENT_BUFFER_SIZE ; 
 scalar_t__ KERN_INVALID_ARGUMENT ; 
 scalar_t__ KERN_SUCCESS ; 
 uintptr_t PAGE_SIZE ; 
 scalar_t__ thread_get_state (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  x86_THREAD_STATE64 ; 
 int /*<<< orphan*/  x86_THREAD_STATE64_COUNT ; 

kern_return_t
thread_get_register_pointer_values(thread_t thread, uintptr_t *sp, size_t *length, uintptr_t *values)
{
    if (!length) return KERN_INVALID_ARGUMENT;
    if (*length > 0 && values == NULL) return KERN_INVALID_ARGUMENT;

    size_t in_length = *length;
    size_t out_length = 0;

#if defined(__i386__)
    i386_thread_state_t state = {};
    thread_state_flavor_t flavor = x86_THREAD_STATE32;
    mach_msg_type_number_t count = i386_THREAD_STATE_COUNT;
#elif defined(__x86_64__)
    x86_thread_state64_t state = {};
    thread_state_flavor_t flavor = x86_THREAD_STATE64;
    mach_msg_type_number_t count = x86_THREAD_STATE64_COUNT;
#elif defined(__arm__)
    arm_thread_state_t state = {};
    thread_state_flavor_t flavor = ARM_THREAD_STATE;
    mach_msg_type_number_t count = ARM_THREAD_STATE_COUNT;
#elif defined(__arm64__)
    arm_thread_state64_t state = {};
    thread_state_flavor_t flavor = ARM_THREAD_STATE64;
    mach_msg_type_number_t count = ARM_THREAD_STATE64_COUNT;
#else
#error thread_get_register_pointer_values not defined for this architecture
#endif

    kern_return_t ret = thread_get_state(thread, flavor, (thread_state_t)&state, &count);
    if (ret != KERN_SUCCESS){
        return ret;
    }

    // If the provided pointer value is > PAGE_SIZE, add it to the output array
    // if there's available space.  (Values between 0 and PAGE_SIZE are the NULL page
    // and not valid pointers.)
#define push_register_value(p) do { \
    if ((uintptr_t)p > PAGE_SIZE) { \
        if (out_length < in_length && values) \
            values[out_length] = p; \
        out_length++; \
    } } while (0)

#if defined(__i386__)
    if (sp) *sp = state.__esp;

    push_register_value(state.__eax);
    push_register_value(state.__ebx);
    push_register_value(state.__ecx);
    push_register_value(state.__edx);
    push_register_value(state.__edi);
    push_register_value(state.__esi);
    push_register_value(state.__ebp);
#elif defined(__x86_64__)
    if (sp) {
	if (state.__rsp > 128)
		*sp = state.__rsp - 128 /* redzone */;
	else
		*sp = 0;
    }

    push_register_value(state.__rax);
    push_register_value(state.__rbx);
    push_register_value(state.__rcx);
    push_register_value(state.__rdx);
    push_register_value(state.__rdi);
    push_register_value(state.__rbp);
    push_register_value(state.__r8);
    push_register_value(state.__r9);
    push_register_value(state.__r10);
    push_register_value(state.__r11);
    push_register_value(state.__r12);
    push_register_value(state.__r13);
    push_register_value(state.__r14);
    push_register_value(state.__r15);
#elif defined(__arm__)
    if (sp) *sp = state.__sp;

    push_register_value(state.__lr);

    for (int i = 0; i < 13; i++){
        push_register_value(state.__r[i]);
    }
#elif defined(__arm64__)
    if (sp) {
	uintptr_t __sp = arm_thread_state64_get_sp(state);
	if (__sp > 128)
		*sp = __sp - 128 /* redzone */;
	else
		*sp = 0;
    }

    push_register_value(arm_thread_state64_get_lr(state));

    for (int i = 0; i < 29; i++){
        push_register_value(state.__x[i]);
    }
#else
#error thread_get_register_pointer_values not defined for this architecture
#endif

    *length = out_length;

    if (in_length == 0 || out_length > in_length){
        return KERN_INSUFFICIENT_BUFFER_SIZE;
    }

	return KERN_SUCCESS;
}