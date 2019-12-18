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
struct qdio_irq {int /*<<< orphan*/  debug_area; } ;
struct qdio_initialize {unsigned long q_format; unsigned long qib_param_field_format; TYPE_1__* cdev; int /*<<< orphan*/  output_sbal_addr_array; int /*<<< orphan*/  input_sbal_addr_array; int /*<<< orphan*/  flags; int /*<<< orphan*/  int_parm; int /*<<< orphan*/  output_handler; int /*<<< orphan*/  input_handler; int /*<<< orphan*/  no_output_qs; int /*<<< orphan*/  no_input_qs; int /*<<< orphan*/  output_slib_elements; int /*<<< orphan*/  input_slib_elements; int /*<<< orphan*/  qib_param_field; int /*<<< orphan*/ * adapter_name; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBF_DEV_EVENT (int /*<<< orphan*/ ,struct qdio_irq*,char*) ; 
 int /*<<< orphan*/  DBF_ERR ; 
 int /*<<< orphan*/  DBF_EVENT (char*,unsigned long,...) ; 
 int /*<<< orphan*/  DBF_HEX (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  DBF_WARN ; 
 int /*<<< orphan*/  debug_hex_ascii_view ; 
 int /*<<< orphan*/  debug_register (char*,int,int,int) ; 
 int /*<<< orphan*/  debug_register_view (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debug_set_level (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* dev_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

void qdio_allocate_dbf(struct qdio_initialize *init_data,
		       struct qdio_irq *irq_ptr)
{
	char text[20];

	DBF_EVENT("qfmt:%1d", init_data->q_format);
	DBF_HEX(init_data->adapter_name, 8);
	DBF_EVENT("qpff%4x", init_data->qib_param_field_format);
	DBF_HEX(&init_data->qib_param_field, sizeof(void *));
	DBF_HEX(&init_data->input_slib_elements, sizeof(void *));
	DBF_HEX(&init_data->output_slib_elements, sizeof(void *));
	DBF_EVENT("niq:%1d noq:%1d", init_data->no_input_qs,
		  init_data->no_output_qs);
	DBF_HEX(&init_data->input_handler, sizeof(void *));
	DBF_HEX(&init_data->output_handler, sizeof(void *));
	DBF_HEX(&init_data->int_parm, sizeof(long));
	DBF_HEX(&init_data->flags, sizeof(long));
	DBF_HEX(&init_data->input_sbal_addr_array, sizeof(void *));
	DBF_HEX(&init_data->output_sbal_addr_array, sizeof(void *));
	DBF_EVENT("irq:%8lx", (unsigned long)irq_ptr);

	/* allocate trace view for the interface */
	snprintf(text, 20, "qdio_%s", dev_name(&init_data->cdev->dev));
	irq_ptr->debug_area = debug_register(text, 2, 1, 16);
	debug_register_view(irq_ptr->debug_area, &debug_hex_ascii_view);
	debug_set_level(irq_ptr->debug_area, DBF_WARN);
	DBF_DEV_EVENT(DBF_ERR, irq_ptr, "dbf created");
}