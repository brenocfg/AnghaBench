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
typedef  int u64 ;
typedef  int u32 ;

/* Variables and functions */
 int EINVAL ; 
 int einj_get_available_error_type (int*) ; 
 int error_type ; 

__attribute__((used)) static int error_type_set(void *data, u64 val)
{
	int rc;
	u32 available_error_type = 0;
	u32 tval, vendor;

	/*
	 * Vendor defined types have 0x80000000 bit set, and
	 * are not enumerated by ACPI_EINJ_GET_ERROR_TYPE
	 */
	vendor = val & 0x80000000;
	tval = val & 0x7fffffff;

	/* Only one error type can be specified */
	if (tval & (tval - 1))
		return -EINVAL;
	if (!vendor) {
		rc = einj_get_available_error_type(&available_error_type);
		if (rc)
			return rc;
		if (!(val & available_error_type))
			return -EINVAL;
	}
	error_type = val;

	return 0;
}