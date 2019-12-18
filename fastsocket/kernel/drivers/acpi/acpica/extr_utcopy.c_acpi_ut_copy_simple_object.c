#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  os_semaphore; } ;
struct TYPE_13__ {int /*<<< orphan*/  os_mutex; } ;
struct TYPE_12__ {int /*<<< orphan*/  handler; } ;
struct TYPE_11__ {int /*<<< orphan*/  object; int /*<<< orphan*/  class; } ;
struct TYPE_10__ {char* pointer; int /*<<< orphan*/  length; } ;
struct TYPE_9__ {char* pointer; int length; } ;
struct TYPE_8__ {int type; int /*<<< orphan*/  flags; union acpi_operand_object* next_object; int /*<<< orphan*/  reference_count; } ;
union acpi_operand_object {TYPE_7__ event; TYPE_6__ mutex; TYPE_5__ region; TYPE_4__ reference; TYPE_3__ string; TYPE_2__ buffer; TYPE_1__ common; } ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_size ;

/* Variables and functions */
 void* ACPI_ALLOCATE (int) ; 
 int /*<<< orphan*/  ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_MEMCPY (char*,char*,int) ; 
 int /*<<< orphan*/  ACPI_NO_UNIT_LIMIT ; 
 int /*<<< orphan*/  ACPI_REFCLASS_TABLE ; 
#define  ACPI_TYPE_BUFFER 133 
#define  ACPI_TYPE_EVENT 132 
#define  ACPI_TYPE_LOCAL_REFERENCE 131 
#define  ACPI_TYPE_MUTEX 130 
#define  ACPI_TYPE_REGION 129 
#define  ACPI_TYPE_STRING 128 
 int /*<<< orphan*/  AE_NO_MEMORY ; 
 int /*<<< orphan*/  AE_OK ; 
 int /*<<< orphan*/  AOPOBJ_STATIC_POINTER ; 
 int /*<<< orphan*/  acpi_os_create_mutex (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_os_create_semaphore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  acpi_ut_add_reference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static acpi_status
acpi_ut_copy_simple_object(union acpi_operand_object *source_desc,
			   union acpi_operand_object *dest_desc)
{
	u16 reference_count;
	union acpi_operand_object *next_object;
	acpi_status status;

	/* Save fields from destination that we don't want to overwrite */

	reference_count = dest_desc->common.reference_count;
	next_object = dest_desc->common.next_object;

	/* Copy the entire source object over the destination object */

	ACPI_MEMCPY((char *)dest_desc, (char *)source_desc,
		    sizeof(union acpi_operand_object));

	/* Restore the saved fields */

	dest_desc->common.reference_count = reference_count;
	dest_desc->common.next_object = next_object;

	/* New object is not static, regardless of source */

	dest_desc->common.flags &= ~AOPOBJ_STATIC_POINTER;

	/* Handle the objects with extra data */

	switch (dest_desc->common.type) {
	case ACPI_TYPE_BUFFER:
		/*
		 * Allocate and copy the actual buffer if and only if:
		 * 1) There is a valid buffer pointer
		 * 2) The buffer has a length > 0
		 */
		if ((source_desc->buffer.pointer) &&
		    (source_desc->buffer.length)) {
			dest_desc->buffer.pointer =
			    ACPI_ALLOCATE(source_desc->buffer.length);
			if (!dest_desc->buffer.pointer) {
				return (AE_NO_MEMORY);
			}

			/* Copy the actual buffer data */

			ACPI_MEMCPY(dest_desc->buffer.pointer,
				    source_desc->buffer.pointer,
				    source_desc->buffer.length);
		}
		break;

	case ACPI_TYPE_STRING:
		/*
		 * Allocate and copy the actual string if and only if:
		 * 1) There is a valid string pointer
		 * (Pointer to a NULL string is allowed)
		 */
		if (source_desc->string.pointer) {
			dest_desc->string.pointer =
			    ACPI_ALLOCATE((acpi_size) source_desc->string.
					  length + 1);
			if (!dest_desc->string.pointer) {
				return (AE_NO_MEMORY);
			}

			/* Copy the actual string data */

			ACPI_MEMCPY(dest_desc->string.pointer,
				    source_desc->string.pointer,
				    (acpi_size) source_desc->string.length + 1);
		}
		break;

	case ACPI_TYPE_LOCAL_REFERENCE:
		/*
		 * We copied the reference object, so we now must add a reference
		 * to the object pointed to by the reference
		 *
		 * DDBHandle reference (from Load/load_table) is a special reference,
		 * it does not have a Reference.Object, so does not need to
		 * increase the reference count
		 */
		if (source_desc->reference.class == ACPI_REFCLASS_TABLE) {
			break;
		}

		acpi_ut_add_reference(source_desc->reference.object);
		break;

	case ACPI_TYPE_REGION:
		/*
		 * We copied the Region Handler, so we now must add a reference
		 */
		if (dest_desc->region.handler) {
			acpi_ut_add_reference(dest_desc->region.handler);
		}
		break;

		/*
		 * For Mutex and Event objects, we cannot simply copy the underlying
		 * OS object. We must create a new one.
		 */
	case ACPI_TYPE_MUTEX:

		status = acpi_os_create_mutex(&dest_desc->mutex.os_mutex);
		if (ACPI_FAILURE(status)) {
			return status;
		}
		break;

	case ACPI_TYPE_EVENT:

		status = acpi_os_create_semaphore(ACPI_NO_UNIT_LIMIT, 0,
						  &dest_desc->event.
						  os_semaphore);
		if (ACPI_FAILURE(status)) {
			return status;
		}
		break;

	default:
		/* Nothing to do for other simple objects */
		break;
	}

	return (AE_OK);
}