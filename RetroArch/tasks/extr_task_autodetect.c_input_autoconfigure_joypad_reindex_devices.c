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
 unsigned int MAX_INPUT_DEVICES ; 
 char* input_config_get_device_name (unsigned int) ; 
 int* input_device_name_index ; 
 scalar_t__ string_is_equal (char const*,char const*) ; 

void input_autoconfigure_joypad_reindex_devices(void)
{
   unsigned i, j, k;

   for(i = 0; i < MAX_INPUT_DEVICES; i++)
      input_device_name_index[i] = 0;

   for(i = 0; i < MAX_INPUT_DEVICES; i++)
   {
      const char *tmp = input_config_get_device_name(i);
      if ( !tmp || input_device_name_index[i] )
         continue;

      k = 2; /*Additional devices start at two*/

      for(j = i+1; j < MAX_INPUT_DEVICES; j++)
      {
         const char *other = input_config_get_device_name(j);

         if (!other)
            continue;

         /*another device with the same name found, for the first time*/
         if (string_is_equal(tmp, other) &&
               input_device_name_index[j]==0 )
         {
            /*Mark the first device of the set*/
            input_device_name_index[i] = 1;
            /*count this additional device, from two up*/
            input_device_name_index[j] = k++;
         }
      }
   }
}