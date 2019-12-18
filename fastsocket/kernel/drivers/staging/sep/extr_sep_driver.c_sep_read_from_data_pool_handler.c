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
struct sep_driver_write_t {int /*<<< orphan*/  num_bytes; int /*<<< orphan*/  datapool_address; int /*<<< orphan*/  app_address; } ;
struct sep_device {void* shared_addr; } ;

/* Variables and functions */
 int EINVAL ; 
 int SEP_DRIVER_DATA_POOL_AREA_OFFSET_IN_BYTES ; 
 int SEP_DRIVER_DATA_POOL_SHARED_AREA_SIZE_IN_BYTES ; 
 int copy_to_user (void*,void*,unsigned long) ; 
 int /*<<< orphan*/  dbg (char*) ; 
 int get_user (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int sep_read_from_data_pool_handler(struct sep_device *sep, unsigned long arg)
{
	int error;
	/* virtual address of dest application buffer */
	unsigned long app_out_address;
	/* virtual address of the data pool */
	unsigned long va;
	void *virt_address;
	unsigned long num_bytes;
	void *data_pool_area_addr;

	dbg("SEP Driver:--------> sep_read_from_data_pool_handler start\n");

	/* get the application address */
	error = get_user(app_out_address, &(((struct sep_driver_write_t *) arg)->app_address));
	if (error)
		goto end_function;

	/* get the virtual kernel address address */
	error = get_user(va, &(((struct sep_driver_write_t *) arg)->datapool_address));
	if (error)
		goto end_function;
	virt_address = (void *)va;

	/* get the number of bytes */
	error = get_user(num_bytes, &(((struct sep_driver_write_t *) arg)->num_bytes));
	if (error)
		goto end_function;

	/* calculate the start of the data pool */
	data_pool_area_addr = sep->shared_addr + SEP_DRIVER_DATA_POOL_AREA_OFFSET_IN_BYTES;

	/* FIXME: These are incomplete all over the driver: what about + len
	   and when doing that also overflows */
	/* check that the range of the virtual kernel address is correct */
	if (virt_address < data_pool_area_addr || virt_address > data_pool_area_addr + SEP_DRIVER_DATA_POOL_SHARED_AREA_SIZE_IN_BYTES) {
		error = -EINVAL;
		goto end_function;
	}

	/* copy the application data */
	error = copy_to_user((void *) app_out_address, virt_address, num_bytes);
end_function:
	dbg("SEP Driver:<-------- sep_read_from_data_pool_handler end\n");
	return error;
}