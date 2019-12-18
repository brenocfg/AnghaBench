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
typedef  size_t u8 ;
struct apei_exec_context {TYPE_1__* ins_table; } ;
struct acpi_whea_header {size_t instruction; int /*<<< orphan*/  register_region; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int APEI_EXEC_INS_ACCESS_REGISTER ; 
 int apei_map_generic_address (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pre_map_gar_callback(struct apei_exec_context *ctx,
				struct acpi_whea_header *entry,
				void *data)
{
	u8 ins = entry->instruction;

	if (ctx->ins_table[ins].flags & APEI_EXEC_INS_ACCESS_REGISTER)
		return apei_map_generic_address(&entry->register_region);

	return 0;
}