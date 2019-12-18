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
 int /*<<< orphan*/  VIDEOCORE_PREFIX ; 
 int /*<<< orphan*/  mmal_component_supplier_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_vc_component_create ; 
 int /*<<< orphan*/  mmal_vc_shm_init () ; 

void mmal_register_component_videocore(void)
{
   mmal_vc_shm_init();
   mmal_component_supplier_register(VIDEOCORE_PREFIX, mmal_vc_component_create);
}