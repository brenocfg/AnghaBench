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
struct TYPE_3__ {scalar_t__* roles; } ;
typedef  int /*<<< orphan*/  MMAL_BOOL_T ;
typedef  scalar_t__ MMALOMX_ROLE_T ;

/* Variables and functions */
 scalar_t__ MMALOMX_ROLE_UNDEFINED ; 
 int MMAL_COUNTOF (TYPE_1__*) ; 
 int /*<<< orphan*/  MMAL_FALSE ; 
 int /*<<< orphan*/  MMAL_TRUE ; 
 TYPE_1__* mmalomx_components ; 

MMAL_BOOL_T mmalomx_registry_component_supports_role(int id, MMALOMX_ROLE_T role)
{
   unsigned int i;

   if (id >= (int)MMAL_COUNTOF(mmalomx_components) || id < 0)
      id = MMAL_COUNTOF(mmalomx_components) - 1;

   for (i = 0; mmalomx_components[id].roles[i] != MMALOMX_ROLE_UNDEFINED; i++)
      if (mmalomx_components[id].roles[i] == role)
         return MMAL_TRUE;

   return MMAL_FALSE;
}