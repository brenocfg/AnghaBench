#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int handler_flags; int /*<<< orphan*/  context; int /*<<< orphan*/  (* handler ) (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ;int /*<<< orphan*/  (* setup ) (union acpi_operand_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ;} ;
struct TYPE_5__ {int flags; int /*<<< orphan*/  space_id; scalar_t__ address; union acpi_operand_object* handler; int /*<<< orphan*/  node; } ;
struct TYPE_4__ {void* region_context; } ;
union acpi_operand_object {TYPE_3__ address_space; TYPE_2__ region; TYPE_1__ extra; } ;
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  acpi_status ;
typedef  int /*<<< orphan*/  acpi_integer ;
typedef  int /*<<< orphan*/  (* acpi_adr_space_setup ) (union acpi_operand_object*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ;
typedef  int /*<<< orphan*/  (* acpi_adr_space_handler ) (scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*) ;

/* Variables and functions */
 int ACPI_ADDR_HANDLER_DEFAULT_INSTALLED ; 
 int /*<<< orphan*/  ACPI_DB_OPREGION ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_EXCEPTION (int /*<<< orphan*/ ) ; 
 scalar_t__ ACPI_FAILURE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_FORMAT_NATIVE_UINT (scalar_t__) ; 
 int /*<<< orphan*/  ACPI_FREE (void*) ; 
 int /*<<< orphan*/  ACPI_FUNCTION_TRACE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_REGION_ACTIVATE ; 
 int /*<<< orphan*/  AE_INFO ; 
 int /*<<< orphan*/  AE_NOT_EXIST ; 
 int AOPOBJ_SETUP_COMPLETE ; 
 int /*<<< orphan*/  acpi_ex_enter_interpreter () ; 
 int /*<<< orphan*/  acpi_ex_exit_interpreter () ; 
 union acpi_operand_object* acpi_ns_get_secondary_object (union acpi_operand_object*) ; 
 int /*<<< orphan*/  acpi_ut_get_node_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  acpi_ut_get_region_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ev_address_space_dispatch ; 
 int /*<<< orphan*/  return_ACPI_STATUS (int /*<<< orphan*/ ) ; 

acpi_status
acpi_ev_address_space_dispatch(union acpi_operand_object *region_obj,
			       u32 function,
			       u32 region_offset,
			       u32 bit_width, acpi_integer * value)
{
	acpi_status status;
	acpi_adr_space_handler handler;
	acpi_adr_space_setup region_setup;
	union acpi_operand_object *handler_desc;
	union acpi_operand_object *region_obj2;
	void *region_context = NULL;

	ACPI_FUNCTION_TRACE(ev_address_space_dispatch);

	region_obj2 = acpi_ns_get_secondary_object(region_obj);
	if (!region_obj2) {
		return_ACPI_STATUS(AE_NOT_EXIST);
	}

	/* Ensure that there is a handler associated with this region */

	handler_desc = region_obj->region.handler;
	if (!handler_desc) {
		ACPI_ERROR((AE_INFO,
			    "No handler for Region [%4.4s] (%p) [%s]",
			    acpi_ut_get_node_name(region_obj->region.node),
			    region_obj,
			    acpi_ut_get_region_name(region_obj->region.
						    space_id)));

		return_ACPI_STATUS(AE_NOT_EXIST);
	}

	/*
	 * It may be the case that the region has never been initialized.
	 * Some types of regions require special init code
	 */
	if (!(region_obj->region.flags & AOPOBJ_SETUP_COMPLETE)) {

		/* This region has not been initialized yet, do it */

		region_setup = handler_desc->address_space.setup;
		if (!region_setup) {

			/* No initialization routine, exit with error */

			ACPI_ERROR((AE_INFO,
				    "No init routine for region(%p) [%s]",
				    region_obj,
				    acpi_ut_get_region_name(region_obj->region.
							    space_id)));
			return_ACPI_STATUS(AE_NOT_EXIST);
		}

		/*
		 * We must exit the interpreter because the region setup will
		 * potentially execute control methods (for example, the _REG method
		 * for this region)
		 */
		acpi_ex_exit_interpreter();

		status = region_setup(region_obj, ACPI_REGION_ACTIVATE,
				      handler_desc->address_space.context,
				      &region_context);

		/* Re-enter the interpreter */

		acpi_ex_enter_interpreter();

		/* Check for failure of the Region Setup */

		if (ACPI_FAILURE(status)) {
			ACPI_EXCEPTION((AE_INFO, status,
					"During region initialization: [%s]",
					acpi_ut_get_region_name(region_obj->
								region.
								space_id)));
			return_ACPI_STATUS(status);
		}

		/* Region initialization may have been completed by region_setup */

		if (!(region_obj->region.flags & AOPOBJ_SETUP_COMPLETE)) {
			region_obj->region.flags |= AOPOBJ_SETUP_COMPLETE;

			if (region_obj2->extra.region_context) {

				/* The handler for this region was already installed */

				ACPI_FREE(region_context);
			} else {
				/*
				 * Save the returned context for use in all accesses to
				 * this particular region
				 */
				region_obj2->extra.region_context =
				    region_context;
			}
		}
	}

	/* We have everything we need, we can invoke the address space handler */

	handler = handler_desc->address_space.handler;

	ACPI_DEBUG_PRINT((ACPI_DB_OPREGION,
			  "Handler %p (@%p) Address %8.8X%8.8X [%s]\n",
			  &region_obj->region.handler->address_space, handler,
			  ACPI_FORMAT_NATIVE_UINT(region_obj->region.address +
						  region_offset),
			  acpi_ut_get_region_name(region_obj->region.
						  space_id)));

	if (!(handler_desc->address_space.handler_flags &
	      ACPI_ADDR_HANDLER_DEFAULT_INSTALLED)) {
		/*
		 * For handlers other than the default (supplied) handlers, we must
		 * exit the interpreter because the handler *might* block -- we don't
		 * know what it will do, so we can't hold the lock on the intepreter.
		 */
		acpi_ex_exit_interpreter();
	}

	/* Call the handler */

	status = handler(function,
			 (region_obj->region.address + region_offset),
			 bit_width, value, handler_desc->address_space.context,
			 region_obj2->extra.region_context);

	if (ACPI_FAILURE(status)) {
		ACPI_EXCEPTION((AE_INFO, status, "Returned by Handler for [%s]",
				acpi_ut_get_region_name(region_obj->region.
							space_id)));
	}

	if (!(handler_desc->address_space.handler_flags &
	      ACPI_ADDR_HANDLER_DEFAULT_INSTALLED)) {
		/*
		 * We just returned from a non-default handler, we must re-enter the
		 * interpreter
		 */
		acpi_ex_enter_interpreter();
	}

	return_ACPI_STATUS(status);
}