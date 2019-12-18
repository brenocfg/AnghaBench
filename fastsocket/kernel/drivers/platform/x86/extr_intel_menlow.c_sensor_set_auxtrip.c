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
struct TYPE_2__ {int value; } ;
union acpi_object {TYPE_1__ integer; int /*<<< orphan*/  member_0; } ;
struct acpi_object_list {int member_0; union acpi_object* member_1; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_handle ;

/* Variables and functions */
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_TYPE_INTEGER ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  GET_AUX0 ; 
 int /*<<< orphan*/  GET_AUX1 ; 
 int /*<<< orphan*/  SET_AUX0 ; 
 int /*<<< orphan*/  SET_AUX1 ; 
 int /*<<< orphan*/  acpi_evaluate_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct acpi_object_list*,unsigned long long*) ; 

__attribute__((used)) static int sensor_set_auxtrip(acpi_handle handle, int index, int value)
{
	acpi_status status;
	union acpi_object arg = {
		ACPI_TYPE_INTEGER
	};
	struct acpi_object_list args = {
		1, &arg
	};
	unsigned long long temp;

	if (index != 0 && index != 1)
		return -EINVAL;

	status = acpi_evaluate_integer(handle, index ? GET_AUX0 : GET_AUX1,
				       NULL, &temp);
	if (ACPI_FAILURE(status))
		return -EIO;
	if ((index && value < temp) || (!index && value > temp))
		return -EINVAL;

	arg.integer.value = value;
	status = acpi_evaluate_integer(handle, index ? SET_AUX1 : SET_AUX0,
				       &args, &temp);
	if (ACPI_FAILURE(status))
		return -EIO;

	/* do we need to check the return value of SAX0/SAX1 ? */

	return 0;
}