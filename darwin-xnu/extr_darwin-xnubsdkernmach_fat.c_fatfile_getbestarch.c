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

/* Variables and functions */
 int /*<<< orphan*/  CPU_ARCH_MASK ; 
 int /*<<< orphan*/  cpu_type () ; 
 int /*<<< orphan*/  fatfile_getarch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct fat_arch*) ; 

load_return_t
fatfile_getbestarch(
		vm_offset_t		data_ptr,
		vm_size_t		data_size,
		struct fat_arch	*archret)
{
	/*
	 * Ignore all architectural bits when determining if an image
	 * in a fat file should be skipped or graded.
	 */
	return fatfile_getarch(data_ptr, data_size, cpu_type(), CPU_ARCH_MASK, archret);
}