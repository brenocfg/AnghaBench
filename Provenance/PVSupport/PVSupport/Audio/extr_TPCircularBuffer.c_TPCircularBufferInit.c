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
typedef  int /*<<< orphan*/  vm_prot_t ;
typedef  scalar_t__ vm_address_t ;
typedef  scalar_t__ kern_return_t ;
struct TYPE_3__ {int length; scalar_t__ tail; scalar_t__ head; scalar_t__ fillCount; void* buffer; } ;
typedef  TYPE_1__ TPCircularBuffer ;

/* Variables and functions */
 scalar_t__ ERR_SUCCESS ; 
 int /*<<< orphan*/  VM_FLAGS_ANYWHERE ; 
 int /*<<< orphan*/  VM_INHERIT_DEFAULT ; 
 int /*<<< orphan*/  mach_task_self () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  reportResult (scalar_t__,char*) ; 
 int round_page (int) ; 
 scalar_t__ vm_allocate (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ vm_deallocate (int /*<<< orphan*/ ,scalar_t__,int) ; 
 scalar_t__ vm_remap (int /*<<< orphan*/ ,scalar_t__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool TPCircularBufferInit(TPCircularBuffer *buffer, int length) {

    // Keep trying until we get our buffer, needed to handle race conditions
    int retries = 3;
    while ( true ) {

        buffer->length = round_page(length);    // We need whole page sizes

        // Temporarily allocate twice the length, so we have the contiguous address space to
        // support a second instance of the buffer directly after
        vm_address_t bufferAddress;
        kern_return_t result = vm_allocate(mach_task_self(),
                                           &bufferAddress,
                                           buffer->length * 2,
                                           VM_FLAGS_ANYWHERE); // allocate anywhere it'll fit
        if ( result != ERR_SUCCESS ) {
            if ( retries-- == 0 ) {
                reportResult(result, "Buffer allocation");
                return false;
            }
            // Try again if we fail
            continue;
        }

        // Now replace the second half of the allocation with a virtual copy of the first half. Deallocate the second half...
        result = vm_deallocate(mach_task_self(),
                               bufferAddress + buffer->length,
                               buffer->length);
        if ( result != ERR_SUCCESS ) {
            if ( retries-- == 0 ) {
                reportResult(result, "Buffer deallocation");
                return false;
            }
            // If this fails somehow, deallocate the whole region and try again
            vm_deallocate(mach_task_self(), bufferAddress, buffer->length);
            continue;
        }

        // Re-map the buffer to the address space immediately after the buffer
        vm_address_t virtualAddress = bufferAddress + buffer->length;
        vm_prot_t cur_prot, max_prot;
        result = vm_remap(mach_task_self(),
                          &virtualAddress,   // mirror target
                          buffer->length,    // size of mirror
                          0,                 // auto alignment
                          0,                 // force remapping to virtualAddress
                          mach_task_self(),  // same task
                          bufferAddress,     // mirror source
                          0,                 // MAP READ-WRITE, NOT COPY
                          &cur_prot,         // unused protection struct
                          &max_prot,         // unused protection struct
                          VM_INHERIT_DEFAULT);
        if ( result != ERR_SUCCESS ) {
            if ( retries-- == 0 ) {
                reportResult(result, "Remap buffer memory");
                return false;
            }
            // If this remap failed, we hit a race condition, so deallocate and try again
            vm_deallocate(mach_task_self(), bufferAddress, buffer->length);
            continue;
        }

        if ( virtualAddress != bufferAddress+buffer->length ) {
            // If the memory is not contiguous, clean up both allocated buffers and try again
            if ( retries-- == 0 ) {
                printf("Couldn't map buffer memory to end of buffer\n");
                return false;
            }

            vm_deallocate(mach_task_self(), virtualAddress, buffer->length);
            vm_deallocate(mach_task_self(), bufferAddress, buffer->length);
            continue;
        }

        buffer->buffer = (void*)bufferAddress;
        buffer->fillCount = 0;
        buffer->head = buffer->tail = 0;

        return true;
    }
    return false;
}