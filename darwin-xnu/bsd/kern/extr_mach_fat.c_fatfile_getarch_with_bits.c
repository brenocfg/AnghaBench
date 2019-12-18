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
typedef  int /*<<< orphan*/  vm_size_t ;
typedef  int /*<<< orphan*/  vm_offset_t ;
struct fat_arch {int dummy; } ;
typedef  int /*<<< orphan*/  load_return_t ;
typedef  int integer_t ;

/* Variables and functions */
 int CPU_ARCH_MASK ; 
 int cpu_type () ; 
 int /*<<< orphan*/  fatfile_getarch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,struct fat_arch*) ; 

load_return_t
fatfile_getarch_with_bits(
	integer_t		archbits,
	vm_offset_t 	data_ptr,
	vm_size_t		data_size,
	struct fat_arch		*archret)
{
	/*
	 * Scan the fat_arch array for matches with the requested
	 * architectural bits set, and for the current hardware cpu CPU.
	 */
	return fatfile_getarch(data_ptr, data_size, (archbits & CPU_ARCH_MASK) | (cpu_type() & ~CPU_ARCH_MASK), 0, archret);
}