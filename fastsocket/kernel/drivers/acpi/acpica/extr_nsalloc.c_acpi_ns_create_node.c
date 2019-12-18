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
typedef  scalar_t__ u32 ;
struct TYPE_3__ {scalar_t__ integer; } ;
struct acpi_namespace_node {TYPE_1__ name; } ;
struct TYPE_4__ {scalar_t__ total_allocated; scalar_t__ total_freed; scalar_t__ max_occupied; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DESC_TYPE_NAMED ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MEM_TRACKING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SET_DESCRIPTOR_TYPE (struct acpi_namespace_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_gbl_namespace_cache ; 
 TYPE_2__* acpi_gbl_ns_node_list ; 
 struct acpi_namespace_node* acpi_os_acquire_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ns_create_node ; 
 int /*<<< orphan*/  return_PTR (struct acpi_namespace_node*) ; 

struct acpi_namespace_node *acpi_ns_create_node(u32 name)
{
	struct acpi_namespace_node *node;
#ifdef ACPI_DBG_TRACK_ALLOCATIONS
	u32 temp;
#endif

	ACPI_FUNCTION_TRACE(ns_create_node);

	node = acpi_os_acquire_object(acpi_gbl_namespace_cache);
	if (!node) {
		return_PTR(NULL);
	}

	ACPI_MEM_TRACKING(acpi_gbl_ns_node_list->total_allocated++);

#ifdef ACPI_DBG_TRACK_ALLOCATIONS
	temp = acpi_gbl_ns_node_list->total_allocated -
	    acpi_gbl_ns_node_list->total_freed;
	if (temp > acpi_gbl_ns_node_list->max_occupied) {
		acpi_gbl_ns_node_list->max_occupied = temp;
	}
#endif

	node->name.integer = name;
	ACPI_SET_DESCRIPTOR_TYPE(node, ACPI_DESC_TYPE_NAMED);
	return_PTR(node);
}