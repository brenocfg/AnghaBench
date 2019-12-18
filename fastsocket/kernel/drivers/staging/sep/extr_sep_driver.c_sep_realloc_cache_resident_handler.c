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
struct sep_driver_realloc_cache_resident_t {scalar_t__ new_base_addr; scalar_t__ new_cache_addr; scalar_t__ new_resident_addr; scalar_t__ new_shared_area_addr; } ;
struct sep_device {scalar_t__ shared_bus; scalar_t__ resident_bus; scalar_t__ rar_bus; } ;

/* Variables and functions */
 int EFAULT ; 
 scalar_t__ copy_to_user (void*,struct sep_driver_realloc_cache_resident_t*,int) ; 
 int /*<<< orphan*/  edbg (char*,scalar_t__) ; 
 int sep_load_firmware (struct sep_device*) ; 

__attribute__((used)) static int sep_realloc_cache_resident_handler(struct sep_device *sep,
						unsigned long arg)
{
	struct sep_driver_realloc_cache_resident_t command_args;
	int error;

	/* copy cache and resident to the their intended locations */
	error = sep_load_firmware(sep);
	if (error)
		return error;

	command_args.new_base_addr = sep->shared_bus;

	/* find the new base address according to the lowest address between
	   cache, resident and shared area */
	if (sep->resident_bus < command_args.new_base_addr)
		command_args.new_base_addr = sep->resident_bus;
	if (sep->rar_bus < command_args.new_base_addr)
		command_args.new_base_addr = sep->rar_bus;

	/* set the return parameters */
	command_args.new_cache_addr = sep->rar_bus;
	command_args.new_resident_addr = sep->resident_bus;

	/* set the new shared area */
	command_args.new_shared_area_addr = sep->shared_bus;

	edbg("SEP Driver:command_args.new_shared_addr is %08llx\n", command_args.new_shared_area_addr);
	edbg("SEP Driver:command_args.new_base_addr is %08llx\n", command_args.new_base_addr);
	edbg("SEP Driver:command_args.new_resident_addr is %08llx\n", command_args.new_resident_addr);
	edbg("SEP Driver:command_args.new_rar_addr is %08llx\n", command_args.new_cache_addr);

	/* return to user */
	if (copy_to_user((void *) arg, &command_args, sizeof(struct sep_driver_realloc_cache_resident_t)))
		return -EFAULT;
	return 0;
}