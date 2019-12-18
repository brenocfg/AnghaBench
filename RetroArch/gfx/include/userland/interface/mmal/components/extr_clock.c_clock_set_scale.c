#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int clock_num; TYPE_2__* priv; int /*<<< orphan*/ * clock; } ;
struct TYPE_6__ {TYPE_1__* module; } ;
struct TYPE_5__ {scalar_t__ pending_scale; } ;
typedef  int /*<<< orphan*/  MMAL_RATIONAL_T ;
typedef  TYPE_3__ MMAL_COMPONENT_T ;

/* Variables and functions */
 int /*<<< orphan*/  mmal_port_clock_scale_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clock_set_scale(MMAL_COMPONENT_T *component, MMAL_RATIONAL_T scale)
{
   unsigned i;

   for (i = 0; i < component->clock_num; ++i)
      mmal_port_clock_scale_set(component->clock[i], scale);

   component->priv->module->pending_scale = 0;
}