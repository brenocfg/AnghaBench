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
struct acpi_processor {int throttling_platform_limit; int /*<<< orphan*/  handle; } ;
typedef  scalar_t__ acpi_status ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (scalar_t__) ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__ AE_NOT_FOUND ; 
 int EINVAL ; 
 int ENODEV ; 
 scalar_t__ acpi_evaluate_integer (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,unsigned long long*) ; 
 scalar_t__ ignore_tpc ; 

__attribute__((used)) static int acpi_processor_get_platform_limit(struct acpi_processor *pr)
{
	acpi_status status = 0;
	unsigned long long tpc = 0;

	if (!pr)
		return -EINVAL;

	if (ignore_tpc)
		goto end;

	status = acpi_evaluate_integer(pr->handle, "_TPC", NULL, &tpc);
	if (ACPI_FAILURE(status)) {
		if (status != AE_NOT_FOUND) {
			ACPI_EXCEPTION((AE_INFO, status, "Evaluating _TPC"));
		}
		return -ENODEV;
	}

end:
	pr->throttling_platform_limit = (int)tpc;
	return 0;
}