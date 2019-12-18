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
struct tm {int dummy; } ;
typedef  int /*<<< orphan*/  runtime_log_t ;

/* Variables and functions */
 int /*<<< orphan*/  LC_TIME ; 
 int /*<<< orphan*/  free (char*) ; 
 char* local_to_utf8_string_alloc (char*) ; 
 int /*<<< orphan*/  runtime_log_get_last_played_time (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  setlocale (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strftime (char*,size_t,char const*,struct tm*) ; 
 int /*<<< orphan*/  string_is_empty (char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,size_t) ; 

__attribute__((used)) static void last_played_strftime(runtime_log_t *runtime_log, char *str, size_t len, const char *format)
{
   struct tm time_info;
   char *local = NULL;

   if (!runtime_log)
      return;

   /* Get time */
   runtime_log_get_last_played_time(runtime_log, &time_info);

   /* Ensure correct locale is set */
   setlocale(LC_TIME, "");

   /* Generate string */
#if defined(__linux__) && !defined(ANDROID)
   strftime(str, len, format, &time_info);
#else
   strftime(str, len, format, &time_info);
   local = local_to_utf8_string_alloc(str);

   if (!string_is_empty(local))
      strlcpy(str, local, len);

   if (local)
   {
      free(local);
      local = NULL;
   }
#endif
}