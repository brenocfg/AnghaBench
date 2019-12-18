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

/* Variables and functions */
 int /*<<< orphan*/  mmal_component_create_null_sink ; 
 int /*<<< orphan*/  mmal_component_supplier_register (char*,int /*<<< orphan*/ ) ; 

void mmal_register_component_null_sink(void)
{
   mmal_component_supplier_register("null_sink", mmal_component_create_null_sink);
}