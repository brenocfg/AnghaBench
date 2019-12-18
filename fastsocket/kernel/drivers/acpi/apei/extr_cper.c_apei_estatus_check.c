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
struct acpi_hest_generic_status {unsigned int data_length; } ;
struct acpi_hest_generic_data {unsigned int error_data_length; } ;

/* Variables and functions */
 int EINVAL ; 
 int apei_estatus_check_header (struct acpi_hest_generic_status const*) ; 

int apei_estatus_check(const struct acpi_hest_generic_status *estatus)
{
	struct acpi_hest_generic_data *gdata;
	unsigned int data_len, gedata_len;
	int rc;

	rc = apei_estatus_check_header(estatus);
	if (rc)
		return rc;
	data_len = estatus->data_length;
	gdata = (struct acpi_hest_generic_data *)(estatus + 1);
	while (data_len >= sizeof(*gdata)) {
		gedata_len = gdata->error_data_length;
		if (gedata_len > data_len - sizeof(*gdata))
			return -EINVAL;
		data_len -= gedata_len + sizeof(*gdata);
		gdata = (void *)(gdata + 1) + gedata_len;
	}
	if (data_len)
		return -EINVAL;

	return 0;
}