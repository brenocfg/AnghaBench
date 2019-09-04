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
typedef  scalar_t__ uint64_t ;
struct pal_efi_registers {scalar_t__ rax; } ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,scalar_t__,struct pal_efi_registers*,void*,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  KERN_INVALID_ADDRESS ; 
 int /*<<< orphan*/  KERN_INVALID_ARGUMENT ; 
 int /*<<< orphan*/  KERN_NOT_SUPPORTED ; 
 int /*<<< orphan*/  KERN_SUCCESS ; 
 scalar_t__ VM_MIN_KERNEL_ADDRESS ; 
 int /*<<< orphan*/  _pal_efi_call_in_64bit_mode_asm (scalar_t__,struct pal_efi_registers*,void*,size_t) ; 
 int /*<<< orphan*/  gPEEFIRuntimeServices ; 
 int /*<<< orphan*/  gPEEFISystemTable ; 

kern_return_t
pal_efi_call_in_64bit_mode(uint64_t func,
                           struct pal_efi_registers *efi_reg,
                           void *stack_contents,
                           size_t stack_contents_size, /* 16-byte multiple */
                           uint64_t *efi_status)
{
    DBG("pal_efi_call_in_64bit_mode(0x%016llx, %p, %p, %lu, %p)\n",
        func, efi_reg, stack_contents, stack_contents_size, efi_status);

    if (func == 0) {
        return KERN_INVALID_ADDRESS;
    }

    if ((efi_reg == NULL)
        || (stack_contents == NULL)
        || (stack_contents_size % 16 != 0)) {
        return KERN_INVALID_ARGUMENT;
    }

    if (!gPEEFISystemTable || !gPEEFIRuntimeServices) {
        return KERN_NOT_SUPPORTED;
    }

    if (func < VM_MIN_KERNEL_ADDRESS) {
        /*
         * EFI Runtime Services must be mapped in our address
         * space at an appropriate location.
         */
        return KERN_INVALID_ADDRESS;
    }

    _pal_efi_call_in_64bit_mode_asm(func,
                                    efi_reg,
                                    stack_contents,
                                    stack_contents_size);

    *efi_status = efi_reg->rax;

    return KERN_SUCCESS;
}