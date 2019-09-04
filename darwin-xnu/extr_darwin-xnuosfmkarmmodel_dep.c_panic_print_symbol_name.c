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

void panic_print_symbol_name(vm_address_t search)
{
#pragma unused(search)
	// empty stub. Really only used on x86_64.
	return;
}