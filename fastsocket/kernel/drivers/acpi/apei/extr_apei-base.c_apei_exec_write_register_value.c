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
struct apei_exec_context {int /*<<< orphan*/  value; } ;
struct acpi_whea_header {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int apei_exec_write_register (struct apei_exec_context*,struct acpi_whea_header*) ; 

int apei_exec_write_register_value(struct apei_exec_context *ctx,
				   struct acpi_whea_header *entry)
{
	int rc;

	ctx->value = entry->value;
	rc = apei_exec_write_register(ctx, entry);

	return rc;
}