#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  name ;
struct TYPE_8__ {char* name; int /*<<< orphan*/  index; } ;
typedef  TYPE_1__ blissbox_pad_type_t ;
struct TYPE_9__ {scalar_t__ vid; scalar_t__ pid; int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ autoconfig_params_t ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 scalar_t__ BLISSBOX_MAX_PAD_INDEX ; 
 scalar_t__ BLISSBOX_OLD_PID ; 
 scalar_t__ BLISSBOX_PID ; 
 scalar_t__ BLISSBOX_UPDATE_MODE_PID ; 
 scalar_t__ BLISSBOX_VID ; 
 int /*<<< orphan*/  RARCH_LOG (char*,...) ; 
 TYPE_1__* blissbox_pad_types ; 
 TYPE_1__ const** blissbox_pads ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 TYPE_1__* input_autoconfigure_get_blissbox_pad_type (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 

__attribute__((used)) static void input_autoconfigure_override_handler(autoconfig_params_t *params)
{
   if (params->vid == BLISSBOX_VID)
   {
      if (params->pid == BLISSBOX_UPDATE_MODE_PID)
         RARCH_LOG("[Autoconf]: Bliss-Box in update mode detected. Ignoring.\n");
      else if (params->pid == BLISSBOX_OLD_PID)
         RARCH_LOG("[Autoconf]: Bliss-Box 1.0 firmware detected. Please update to 2.0 or later.\n");
      else if (params->pid >= BLISSBOX_PID && params->pid <= BLISSBOX_PID + BLISSBOX_MAX_PAD_INDEX)
      {
         const blissbox_pad_type_t *pad;
         char name[255] = {0};
         int index      = params->pid - BLISSBOX_PID;

         RARCH_LOG("[Autoconf]: Bliss-Box detected. Getting pad type...\n");

         if (blissbox_pads[index])
            pad = blissbox_pads[index];
         else
            pad = input_autoconfigure_get_blissbox_pad_type(params->vid, params->pid);

         if (pad && !string_is_empty(pad->name))
         {
            RARCH_LOG("[Autoconf]: Found Bliss-Box pad type: %s (%d) in port#%d\n", pad->name, pad->index, index);

            if (params->name)
               free(params->name);

            /* override name given to autoconfig so it knows what kind of pad this is */
            strlcat(name, "Bliss-Box 4-Play ", sizeof(name));
            strlcat(name, pad->name, sizeof(name));

            params->name = strdup(name);

            blissbox_pads[index] = pad;
         }
         /* use NULL entry to mark as an unconnected port */
         else
            blissbox_pads[index] = &blissbox_pad_types[ARRAY_SIZE(blissbox_pad_types) - 1];
      }
   }
}