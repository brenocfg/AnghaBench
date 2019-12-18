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
typedef  int /*<<< orphan*/  u64 ;
struct apei_exec_context {int /*<<< orphan*/  value; } ;
struct acpi_whea_header {int dummy; } ;

/* Variables and functions */
 int __apei_exec_read_register (struct acpi_whea_header*,int /*<<< orphan*/ *) ; 

int apei_exec_read_register(struct apei_exec_context *ctx,
			    struct acpi_whea_header *entry)
{
	int rc;
	u64 val = 0;

	rc = __apei_exec_read_register(entry, &val);
	if (rc)
		return rc;
	ctx->value = val;

	return 0;
}