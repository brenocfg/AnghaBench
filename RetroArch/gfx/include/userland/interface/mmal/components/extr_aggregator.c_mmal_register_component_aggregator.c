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
 int /*<<< orphan*/  AGGREGATOR_PREFIX ; 
 int /*<<< orphan*/  mmal_component_create_aggregator ; 
 int /*<<< orphan*/  mmal_component_supplier_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void mmal_register_component_aggregator(void)
{
   mmal_component_supplier_register(AGGREGATOR_PREFIX, mmal_component_create_aggregator);
}