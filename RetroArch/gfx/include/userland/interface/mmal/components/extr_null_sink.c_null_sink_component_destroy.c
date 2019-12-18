#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ input_num; int /*<<< orphan*/  input; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  MMAL_SUCCESS ; 
 int /*<<< orphan*/  mmal_ports_free (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static MMAL_STATUS_T null_sink_component_destroy(MMAL_COMPONENT_T *component)
{
   if(component->input_num)
      mmal_ports_free(component->input, component->input_num);
   return MMAL_SUCCESS;
}