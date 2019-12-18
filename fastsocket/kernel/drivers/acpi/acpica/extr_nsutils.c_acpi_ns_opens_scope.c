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
typedef  int u32 ;
typedef  size_t acpi_object_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE_STR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ACPI_NS_NEWSCOPE ; 
 int ACPI_NS_NORMAL ; 
 int /*<<< orphan*/  ACPI_WARNING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AE_INFO ; 
 scalar_t__* acpi_gbl_ns_properties ; 
 int /*<<< orphan*/  acpi_ut_get_type_name (size_t) ; 
 int /*<<< orphan*/  acpi_ut_valid_object_type (size_t) ; 
 int /*<<< orphan*/  ns_opens_scope ; 
 int /*<<< orphan*/  return_UINT32 (int) ; 

u32 acpi_ns_opens_scope(acpi_object_type type)
{
	ACPI_FUNCTION_TRACE_STR(ns_opens_scope, acpi_ut_get_type_name(type));

	if (!acpi_ut_valid_object_type(type)) {

		/* type code out of range  */

		ACPI_WARNING((AE_INFO, "Invalid Object Type %X", type));
		return_UINT32(ACPI_NS_NORMAL);
	}

	return_UINT32(((u32) acpi_gbl_ns_properties[type]) & ACPI_NS_NEWSCOPE);
}