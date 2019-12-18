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
struct sep_driver_build_sync_table_t {int /*<<< orphan*/  isKernelVirtualAddress; int /*<<< orphan*/  table_data_size; int /*<<< orphan*/  in_table_num_entries; int /*<<< orphan*/  in_table_address; scalar_t__ block_size; scalar_t__ data_in_size; scalar_t__ app_in_address; int /*<<< orphan*/  out_table_num_entries; int /*<<< orphan*/  out_table_address; scalar_t__ app_out_address; } ;
struct sep_device {int dummy; } ;

/* Variables and functions */
 int EFAULT ; 
 int copy_from_user (struct sep_driver_build_sync_table_t*,void*,int) ; 
 scalar_t__ copy_to_user (void*,void*,int) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int /*<<< orphan*/  edbg (char*,scalar_t__) ; 
 int sep_prepare_input_dma_table (struct sep_device*,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sep_prepare_input_output_dma_table (struct sep_device*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int sep_create_sync_dma_tables_handler(struct sep_device *sep,
						unsigned long arg)
{
	int error;
	/* command arguments */
	struct sep_driver_build_sync_table_t command_args;

	dbg("SEP Driver:--------> sep_create_sync_dma_tables_handler start\n");

	error = copy_from_user(&command_args, (void *) arg, sizeof(struct sep_driver_build_sync_table_t));
	if (error)
		goto end_function;

	edbg("app_in_address is %08lx\n", command_args.app_in_address);
	edbg("app_out_address is %08lx\n", command_args.app_out_address);
	edbg("data_size is %lu\n", command_args.data_in_size);
	edbg("block_size is %lu\n", command_args.block_size);

	/* check if we need to build only input table or input/output */
	if (command_args.app_out_address)
		/* prepare input and output tables */
		error = sep_prepare_input_output_dma_table(sep,
							   command_args.app_in_address,
							   command_args.app_out_address,
							   command_args.data_in_size,
							   command_args.block_size,
							   &command_args.in_table_address,
							   &command_args.out_table_address, &command_args.in_table_num_entries, &command_args.out_table_num_entries, &command_args.table_data_size, command_args.isKernelVirtualAddress);
	else
		/* prepare input tables */
		error = sep_prepare_input_dma_table(sep,
						    command_args.app_in_address,
						    command_args.data_in_size, command_args.block_size, &command_args.in_table_address, &command_args.in_table_num_entries, &command_args.table_data_size, command_args.isKernelVirtualAddress);

	if (error)
		goto end_function;
	/* copy to user */
	if (copy_to_user((void *) arg, (void *) &command_args, sizeof(struct sep_driver_build_sync_table_t)))
		error = -EFAULT;
end_function:
	dbg("SEP Driver:<-------- sep_create_sync_dma_tables_handler end\n");
	return error;
}