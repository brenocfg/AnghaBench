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
struct TYPE_2__ {char* omx_prefix; scalar_t__ mmal; scalar_t__ omx; } ;

/* Variables and functions */
 char* MMALOMX_COMPONENT_PREFIX ; 
 TYPE_1__* mmalomx_components ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

int mmalomx_registry_find_component(const char *name)
{
   int i, prefix_size;
   const char *prefix;

   for (i = 0; mmalomx_components[i].omx; i++)
   {
      /* Check the prefix first */
      prefix = mmalomx_components[i].omx_prefix;
      if (!prefix)
         prefix = MMALOMX_COMPONENT_PREFIX;
      prefix_size = strlen(prefix);
      if (strncmp(name, prefix, prefix_size))
         continue;

      /* Check the rest of the name */
      if (!strcmp(name + prefix_size, mmalomx_components[i].omx))
         break;
   }

   return mmalomx_components[i].mmal ? i : -1;
}