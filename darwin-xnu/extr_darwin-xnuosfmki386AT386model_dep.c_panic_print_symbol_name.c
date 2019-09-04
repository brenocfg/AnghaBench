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
typedef  int /*<<< orphan*/  vm_address_t ;

/* Variables and functions */
 int /*<<< orphan*/  _mh_execute_header ; 
 int /*<<< orphan*/  panic_print_kmod_symbol_name (int /*<<< orphan*/ ) ; 
 scalar_t__ panic_print_macho_symbol_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void
panic_print_symbol_name(vm_address_t search)
{
    /* try searching in the kernel */
    if (panic_print_macho_symbol_name(&_mh_execute_header, search, "mach_kernel") == 0) {
        /* that failed, now try to search for the right kext */
        panic_print_kmod_symbol_name(search);
    }
}