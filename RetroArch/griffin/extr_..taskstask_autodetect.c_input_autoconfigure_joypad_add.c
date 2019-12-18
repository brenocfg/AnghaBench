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
typedef  int /*<<< orphan*/  retro_task_t ;
typedef  int /*<<< orphan*/  msg ;
typedef  int /*<<< orphan*/  display_name ;
typedef  int /*<<< orphan*/  device_type ;
struct TYPE_8__ {char* path; } ;
typedef  TYPE_1__ config_file_t ;
struct TYPE_9__ {size_t idx; char* name; } ;
typedef  TYPE_2__ autoconfig_params_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEVICE_CONFIGURED_IN_PORT ; 
 int /*<<< orphan*/  config_get_array (TYPE_1__*,char*,char*,int) ; 
 scalar_t__ config_get_bool (TYPE_1__*,char*,int*) ; 
 int /*<<< orphan*/ * input_autoconf_binds ; 
 int /*<<< orphan*/  input_autoconfigure_joypad_conf (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  input_autoconfigure_joypad_reindex_devices () ; 
 int input_autoconfigure_swap_override ; 
 int* input_autoconfigured ; 
 int /*<<< orphan*/  input_config_set_device_config_name (int,char*) ; 
 int /*<<< orphan*/  input_config_set_device_config_path (int,char*) ; 
 int /*<<< orphan*/  input_config_set_device_display_name (int,char*) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char* path_basename (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*,size_t) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 scalar_t__ string_is_empty (char*) ; 
 scalar_t__ string_is_equal (char*,char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/  task_free_title (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  task_set_title (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void input_autoconfigure_joypad_add(config_file_t *conf,
      autoconfig_params_t *params, retro_task_t *task)
{
   char msg[128], display_name[128], device_type[128];
   /* This will be the case if input driver is reinitialized.
    * No reason to spam autoconfigure messages every time. */
   bool block_osd_spam                =
#if defined(HAVE_LIBNX) && defined(HAVE_MENU_WIDGETS)
      true;
#else
      input_autoconfigured[params->idx]
      && !string_is_empty(params->name);
#endif

   msg[0] = display_name[0] = device_type[0] = '\0';

   config_get_array(conf, "input_device_display_name",
         display_name, sizeof(display_name));
   config_get_array(conf, "input_device_type", device_type,
         sizeof(device_type));

   input_autoconfigured[params->idx] = true;

   input_autoconfigure_joypad_conf(conf,
         input_autoconf_binds[params->idx]);

   if (string_is_equal(device_type, "remote"))
   {
      static bool remote_is_bound        = false;
      const char *autoconfig_str         = (string_is_empty(display_name) &&
            !string_is_empty(params->name)) ? params->name : (!string_is_empty(display_name) ? display_name : "N/A");
      strlcpy(msg, autoconfig_str, sizeof(msg));
      strlcat(msg, " configured.", sizeof(msg));

      if (!remote_is_bound)
      {
         task_free_title(task);
         task_set_title(task, strdup(msg));
      }
      remote_is_bound = true;
      if (params->idx == 0)
         input_autoconfigure_swap_override = true;
   }
   else
   {
      bool tmp                    = false;
      const char *autoconfig_str  = (string_is_empty(display_name) &&
            !string_is_empty(params->name))
            ? params->name : (!string_is_empty(display_name) ? display_name : "N/A");

      snprintf(msg, sizeof(msg), "%s %s #%u.",
            autoconfig_str,
            msg_hash_to_str(MSG_DEVICE_CONFIGURED_IN_PORT),
            params->idx);

      /* allow overriding the swap menu controls for player 1*/
      if (params->idx == 0)
      {
         if (config_get_bool(conf, "input_swap_override", &tmp))
            input_autoconfigure_swap_override = tmp;
         else
            input_autoconfigure_swap_override = false;
      }

      if (!block_osd_spam)
      {
         task_free_title(task);
         task_set_title(task, strdup(msg));
      }
   }
   if (!string_is_empty(display_name))
      input_config_set_device_display_name(params->idx, display_name);
   else
      input_config_set_device_display_name(params->idx, params->name);
   if (!string_is_empty(conf->path))
   {
      input_config_set_device_config_name(params->idx, path_basename(conf->path));
      input_config_set_device_config_path(params->idx, conf->path);
   }
   else
   {
      input_config_set_device_config_name(params->idx, "N/A");
      input_config_set_device_config_path(params->idx, "N/A");
   }

   input_autoconfigure_joypad_reindex_devices();
}