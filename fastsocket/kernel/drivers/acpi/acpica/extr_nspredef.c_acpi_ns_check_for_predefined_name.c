#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int expected_btypes; scalar_t__* name; } ;
union acpi_predefined_info {TYPE_2__ info; } ;
struct TYPE_3__ {char* ascii; } ;
struct acpi_namespace_node {TYPE_1__ name; } ;

/* Variables and functions */
 scalar_t__ ACPI_COMPARE_NAME (char*,scalar_t__*) ; 
 int ACPI_RTYPE_PACKAGE ; 
 union acpi_predefined_info* predefined_names ; 

const union acpi_predefined_info *acpi_ns_check_for_predefined_name(struct
								    acpi_namespace_node
								    *node)
{
	const union acpi_predefined_info *this_name;

	/* Quick check for a predefined name, first character must be underscore */

	if (node->name.ascii[0] != '_') {
		return (NULL);
	}

	/* Search info table for a predefined method/object name */

	this_name = predefined_names;
	while (this_name->info.name[0]) {
		if (ACPI_COMPARE_NAME(node->name.ascii, this_name->info.name)) {
			return (this_name);
		}

		/*
		 * Skip next entry in the table if this name returns a Package
		 * (next entry contains the package info)
		 */
		if (this_name->info.expected_btypes & ACPI_RTYPE_PACKAGE) {
			this_name++;
		}

		this_name++;
	}

	return (NULL);		/* Not found */
}