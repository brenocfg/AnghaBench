#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ pointer; } ;
union acpi_object {TYPE_1__ buffer; } ;
typedef  size_t u16 ;
struct radeon_atpx {int /*<<< orphan*/  functions; int /*<<< orphan*/  handle; } ;
struct atpx_verify_interface {size_t version; int /*<<< orphan*/  function_bits; } ;
typedef  int /*<<< orphan*/  output ;

/* Variables and functions */
 int /*<<< orphan*/  ATPX_FUNCTION_VERIFY_INTERFACE ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  kfree (union acpi_object*) ; 
 int /*<<< orphan*/  memcpy (struct atpx_verify_interface*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  memset (struct atpx_verify_interface*,int /*<<< orphan*/ ,int) ; 
 size_t min (int,size_t) ; 
 int /*<<< orphan*/  printk (char*,size_t) ; 
 union acpi_object* radeon_atpx_call (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  radeon_atpx_parse_functions (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int radeon_atpx_verify_interface(struct radeon_atpx *atpx)
{
	union acpi_object *info;
	struct atpx_verify_interface output;
	size_t size;
	int err = 0;

	info = radeon_atpx_call(atpx->handle, ATPX_FUNCTION_VERIFY_INTERFACE, NULL);
	if (!info)
		return -EIO;

	memset(&output, 0, sizeof(output));

	size = *(u16 *) info->buffer.pointer;
	if (size < 8) {
		printk("ATPX buffer is too small: %zu\n", size);
		err = -EINVAL;
		goto out;
	}
	size = min(sizeof(output), size);

	memcpy(&output, info->buffer.pointer, size);

	/* TODO: check version? */
	printk("ATPX version %u\n", output.version);

	radeon_atpx_parse_functions(&atpx->functions, output.function_bits);

out:
	kfree(info);
	return err;
}