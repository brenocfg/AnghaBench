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
struct TYPE_2__ {int cm_supported; int /*<<< orphan*/  handle; } ;

/* Variables and functions */
 int ENODEV ; 
 char** cm_getv ; 
 TYPE_1__* ehotk ; 
 int /*<<< orphan*/  pr_warning (char*,char const*) ; 
 scalar_t__ read_acpi_int (int /*<<< orphan*/ ,char const*,int*) ; 

__attribute__((used)) static int get_acpi(int cm)
{
	int value = -ENODEV;
	if ((ehotk->cm_supported & (0x1 << cm))) {
		const char *method = cm_getv[cm];
		if (method == NULL)
			return -ENODEV;
		if (read_acpi_int(ehotk->handle, method, &value))
			pr_warning("Error reading %s\n", method);
	}
	return value;
}