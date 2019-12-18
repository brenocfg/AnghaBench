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
struct sep_driver_get_mapped_offset_t {scalar_t__ physical_address; scalar_t__ offset; } ;
struct sep_device {scalar_t__ shared_bus; } ;

/* Variables and functions */
 int EINVAL ; 
 int copy_from_user (struct sep_driver_get_mapped_offset_t*,void*,int) ; 
 int copy_to_user (void*,struct sep_driver_get_mapped_offset_t*,int) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  edbg (char*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int sep_get_physical_mapped_offset_handler(struct sep_device *sep, unsigned long arg)
{
	int error;
	struct sep_driver_get_mapped_offset_t command_args;

	dbg("SEP Driver:--------> sep_get_physical_mapped_offset_handler start\n");

	error = copy_from_user(&command_args, (void *) arg, sizeof(struct sep_driver_get_mapped_offset_t));
	if (error)
		goto end_function;

	if (command_args.physical_address < sep->shared_bus) {
		error = -EINVAL;
		goto end_function;
	}

	/*prepare the output parameters in the struct */
	command_args.offset = command_args.physical_address - sep->shared_bus;

	edbg("SEP Driver:bus_address is %08lx, offset is %lu\n", command_args.physical_address, command_args.offset);

	/* send the parameters to user application */
	error = copy_to_user((void *) arg, &command_args, sizeof(struct sep_driver_get_mapped_offset_t));
end_function:
	dbg("SEP Driver:<-------- sep_get_physical_mapped_offset_handler end\n");
	return error;
}