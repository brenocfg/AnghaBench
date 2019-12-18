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
typedef  int /*<<< orphan*/  log ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_FAILED_SAVING_CONFIG_TO ; 
 int /*<<< orphan*/  MSG_SAVED_NEW_CONFIG_TO ; 
 int PATH_MAX_LENGTH ; 
 int /*<<< orphan*/  RARCH_ERR (char*,char*) ; 
 int /*<<< orphan*/  RARCH_LOG (char*,char*) ; 
 int /*<<< orphan*/  RARCH_PATH_CONFIG ; 
 scalar_t__ config_save_file (char const*) ; 
 char* msg_hash_to_str (int /*<<< orphan*/ ) ; 
 char const* path_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,char*,char const*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int) ; 

__attribute__((used)) static bool command_event_save_config(
      const char *config_path,
      char *s, size_t len)
{
   char log[PATH_MAX_LENGTH];
   bool path_exists = !string_is_empty(config_path);
   const char *str  = path_exists ? config_path :
      path_get(RARCH_PATH_CONFIG);

   if (path_exists && config_save_file(config_path))
   {
      snprintf(s, len, "%s \"%s\".",
            msg_hash_to_str(MSG_SAVED_NEW_CONFIG_TO),
            config_path);

      strlcpy(log, "[config] ", sizeof(log));
      strlcat(log, s, sizeof(log));
      RARCH_LOG("%s\n", log);
      return true;
   }

   if (!string_is_empty(str))
   {
      snprintf(s, len, "%s \"%s\".",
            msg_hash_to_str(MSG_FAILED_SAVING_CONFIG_TO),
            str);

      strlcpy(log, "[config] ", sizeof(log));
      strlcat(log, s, sizeof(log));
      RARCH_ERR("%s\n", log);
   }

   return false;
}