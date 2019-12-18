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
typedef  int /*<<< orphan*/  tmp ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 unsigned int MAX_USERS ; 
 int input_autoconfigure_get_device_name_index (unsigned int) ; 
 char* input_config_get_device_config_name (unsigned int) ; 
 char* input_config_get_device_display_name (unsigned int) ; 
 char* input_config_get_device_name (unsigned int) ; 
 int input_config_get_pid (unsigned int) ; 
 int input_config_get_vid (unsigned int) ; 
 scalar_t__ input_is_autoconfigured (unsigned int) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,...) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static int action_bind_sublabel_systeminfo_controller_entry(
      file_list_t *list,
      unsigned type, unsigned i,
      const char *label, const char *path,
      char *s, size_t len)
{
   char tmp[4096];
   unsigned controller;

   for(controller = 0; controller < MAX_USERS; controller++)
   {
      if (input_is_autoconfigured(controller))
      {
            snprintf(tmp, sizeof(tmp), "Port #%d device name: %s (#%d)",
               controller,
               input_config_get_device_name(controller),
               input_autoconfigure_get_device_name_index(controller));

            if (string_is_equal(path, tmp))
               break;
      }
   }
   snprintf(tmp, sizeof(tmp), "Device display name: %s\nDevice config name: %s\nDevice identifiers: %d/%d",
      input_config_get_device_display_name(controller) ? input_config_get_device_display_name(controller) : "N/A",
      input_config_get_device_display_name(controller) ? input_config_get_device_config_name(controller) : "N/A",
      input_config_get_vid(controller), input_config_get_pid(controller));
   strlcpy(s, tmp, len);

   return 0;
}