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
typedef  int /*<<< orphan*/  mach_voucher_attr_recipe_size_t ;
typedef  int /*<<< orphan*/  mach_voucher_attr_raw_recipe_array_t ;
typedef  int /*<<< orphan*/  mach_port_name_t ;
typedef  int kern_return_t ;

/* Variables and functions */
 int MACH_SEND_INVALID_DEST ; 
 int _kernelrpc_host_create_mach_voucher (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int host_create_mach_voucher_trap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

kern_return_t
host_create_mach_voucher(mach_port_name_t host,
                         mach_voucher_attr_raw_recipe_array_t recipes,
                         mach_voucher_attr_recipe_size_t recipesCnt,
                         mach_port_name_t *voucher)
{
	kern_return_t rv;

	rv = host_create_mach_voucher_trap(host, recipes, recipesCnt, voucher);

#ifdef __x86_64__
	/* REMOVE once XBS kernel has new trap */
	if (rv == ((1 << 24) | 70)) /* see mach/i386/syscall_sw.h */
		rv = MACH_SEND_INVALID_DEST;
#elif defined(__i386__)
	/* REMOVE once XBS kernel has new trap */
	if (rv == (kern_return_t)(-70))
		rv = MACH_SEND_INVALID_DEST;
#endif

	if (rv == MACH_SEND_INVALID_DEST)
		rv = _kernelrpc_host_create_mach_voucher(host, recipes, recipesCnt, voucher);

	return rv;
}