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
struct TYPE_2__ {union acpi_operand_object* next_object; } ;
union acpi_operand_object {scalar_t__ type; union acpi_operand_object* object; TYPE_1__ common; } ;
typedef  scalar_t__ u8 ;
struct acpi_namespace_node {scalar_t__ type; struct acpi_namespace_node* object; TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  scalar_t__ acpi_object_type ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_EXEC ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_DESC_TYPE_NAMED ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_GET_DESCRIPTOR_TYPE (union acpi_operand_object*) ; 
 scalar_t__ ACPI_TYPE_ANY ; 
 int /*<<< orphan*/  AE_BAD_PARAMETER ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  acpi_ns_detach_object (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_add_reference (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_get_descriptor_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (union acpi_operand_object*) ; 
 int /*<<< orphan*/  ns_attach_object ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ns_attach_object(struct acpi_namespace_node *node,
		      union acpi_operand_object *object, acpi_object_type type)
{
	union acpi_operand_object *obj_desc;
	union acpi_operand_object *last_obj_desc;
	acpi_object_type object_type = ACPI_TYPE_ANY;

	ACPI_FUNCTION_TRACE(ns_attach_object);

	/*
	 * Parameter validation
	 */
	if (!node) {

		/* Invalid handle */

		ACPI_ERROR((AE_INFO, "Null NamedObj handle"));
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	if (!object && (ACPI_TYPE_ANY != type)) {

		/* Null object */

		ACPI_ERROR((AE_INFO,
			    "Null object, but type not ACPI_TYPE_ANY"));
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	if (ACPI_GET_DESCRIPTOR_TYPE(node) != ACPI_DESC_TYPE_NAMED) {

		/* Not a name handle */

		ACPI_ERROR((AE_INFO, "Invalid handle %p [%s]",
			    node, acpi_ut_get_descriptor_name(node)));
		return_ACPI_STATUS(AE_BAD_PARAMETER);
	}

	/* Check if this object is already attached */

	if (node->object == object) {
		ACPI_DEBUG_PRINT((ACPI_DB_EXEC,
				  "Obj %p already installed in NameObj %p\n",
				  object, node));

		return_ACPI_STATUS(AE_OK);
	}

	/* If null object, we will just install it */

	if (!object) {
		obj_desc = NULL;
		object_type = ACPI_TYPE_ANY;
	}

	/*
	 * If the source object is a namespace Node with an attached object,
	 * we will use that (attached) object
	 */
	else if ((ACPI_GET_DESCRIPTOR_TYPE(object) == ACPI_DESC_TYPE_NAMED) &&
		 ((struct acpi_namespace_node *)object)->object) {
		/*
		 * Value passed is a name handle and that name has a
		 * non-null value.  Use that name's value and type.
		 */
		obj_desc = ((struct acpi_namespace_node *)object)->object;
		object_type = ((struct acpi_namespace_node *)object)->type;
	}

	/*
	 * Otherwise, we will use the parameter object, but we must type
	 * it first
	 */
	else {
		obj_desc = (union acpi_operand_object *)object;

		/* Use the given type */

		object_type = type;
	}

	ACPI_DEBUG_PRINT((ACPI_DB_EXEC, "Installing %p into Node %p [%4.4s]\n",
			  obj_desc, node, acpi_ut_get_node_name(node)));

	/* Detach an existing attached object if present */

	if (node->object) {
		acpi_ns_detach_object(node);
	}

	if (obj_desc) {
		/*
		 * Must increment the new value's reference count
		 * (if it is an internal object)
		 */
		acpi_ut_add_reference(obj_desc);

		/*
		 * Handle objects with multiple descriptors - walk
		 * to the end of the descriptor list
		 */
		last_obj_desc = obj_desc;
		while (last_obj_desc->common.next_object) {
			last_obj_desc = last_obj_desc->common.next_object;
		}

		/* Install the object at the front of the object list */

		last_obj_desc->common.next_object = node->object;
	}

	node->type = (u8) object_type;
	node->object = obj_desc;

	return_ACPI_STATUS(AE_OK);
}