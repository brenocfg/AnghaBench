#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * short_description; int /*<<< orphan*/ * name; int /*<<< orphan*/ * values; scalar_t__ free_flags; } ;
typedef  TYPE_1__ rarch_setting_t ;

/* Variables and functions */
#define  SD_FREE_FLAG_NAME 130 
#define  SD_FREE_FLAG_SHORT 129 
#define  SD_FREE_FLAG_VALUES 128 
 scalar_t__ ST_NONE ; 
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ setting_get_type (TYPE_1__*) ; 

void menu_setting_free(rarch_setting_t *setting)
{
   unsigned values, n;
   rarch_setting_t **list = NULL;

   if (!setting)
      return;

   list                   = (rarch_setting_t**)&setting;

   /* Free data which was previously tagged */
   for (; setting_get_type(setting) != ST_NONE; (*list = *list + 1))
      for (values = (unsigned)setting->free_flags, n = 0; values != 0; values >>= 1, n++)
         if (values & 1)
            switch (1 << n)
            {
               case SD_FREE_FLAG_VALUES:
                  if (setting->values)
                     free((void*)setting->values);
                  setting->values = NULL;
                  break;
               case SD_FREE_FLAG_NAME:
                  if (setting->name)
                     free((void*)setting->name);
                  setting->name = NULL;
                  break;
               case SD_FREE_FLAG_SHORT:
                  if (setting->short_description)
                     free((void*)setting->short_description);
                  setting->short_description = NULL;
                  break;
               default:
                  break;
            }
}