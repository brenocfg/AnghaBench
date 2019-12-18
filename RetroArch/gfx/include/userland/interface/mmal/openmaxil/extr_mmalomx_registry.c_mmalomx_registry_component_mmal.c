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
struct TYPE_3__ {char const* mmal; } ;

/* Variables and functions */
 int MMAL_COUNTOF (TYPE_1__*) ; 
 TYPE_1__* mmalomx_components ; 

const char *mmalomx_registry_component_mmal(int id)
{
   if (id >= (int)MMAL_COUNTOF(mmalomx_components) || id < 0)
      id = MMAL_COUNTOF(mmalomx_components) - 1;

   return mmalomx_components[id].mmal;
}