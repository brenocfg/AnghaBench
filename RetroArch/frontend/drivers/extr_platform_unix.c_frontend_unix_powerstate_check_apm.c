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
typedef  int /*<<< orphan*/  int64_t ;
typedef  enum frontend_powerstate { ____Placeholder_frontend_powerstate } frontend_powerstate ;

/* Variables and functions */
 int FRONTEND_POWERSTATE_CHARGED ; 
 int FRONTEND_POWERSTATE_CHARGING ; 
 int FRONTEND_POWERSTATE_NONE ; 
 int FRONTEND_POWERSTATE_NO_SOURCE ; 
 int FRONTEND_POWERSTATE_ON_POWER_SOURCE ; 
 int /*<<< orphan*/  filestream_exists (int /*<<< orphan*/ ) ; 
 int filestream_read_file (int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  int_string (char*,int*) ; 
 int /*<<< orphan*/  next_string (char**,char**) ; 
 int /*<<< orphan*/  proc_apm_path ; 
 scalar_t__ string_is_equal (char*,char*) ; 
 int strlen (char*) ; 

__attribute__((used)) static bool frontend_unix_powerstate_check_apm(
      enum frontend_powerstate *state,
      int *seconds, int *percent)
{
   size_t str_size     = 0;
   int ac_status       = 0;
   int battery_status  = 0;
   int battery_flag    = 0;
   int battery_percent = 0;
   int battery_time    = 0;
   int64_t length      = 0;
   char *ptr           = NULL;
   char  *buf          = NULL;
   char *str           = NULL;

   if (!filestream_exists(proc_apm_path))
      goto error;

   if (filestream_read_file(proc_apm_path, (void**)&buf, &length) != 1)
      goto error;

   ptr                 = &buf[0];

   if (!next_string(&ptr, &str))     /* driver version */
      goto error;
   if (!next_string(&ptr, &str))     /* BIOS version */
      goto error;
   if (!next_string(&ptr, &str))     /* APM flags */
      goto error;

   if (!next_string(&ptr, &str))     /* AC line status */
      goto error;
   else if (!int_string(str, &ac_status))
      goto error;

   if (!next_string(&ptr, &str))     /* battery status */
      goto error;
   else if (!int_string(str, &battery_status))
      goto error;

   if (!next_string(&ptr, &str))     /* battery flag */
      goto error;
   else if (!int_string(str, &battery_flag))
      goto error;
   if (!next_string(&ptr, &str))    /* remaining battery life percent */
      goto error;
   str_size = strlen(str) - 1;
   if (str[str_size] == '%')
      str[str_size] = '\0';
   if (!int_string(str, &battery_percent))
      goto error;

   if (!next_string(&ptr, &str))     /* remaining battery life time */
      goto error;
   else if (!int_string(str, &battery_time))
      goto error;

   if (!next_string(&ptr, &str))     /* remaining battery life time units */
      goto error;
   else if (string_is_equal(str, "min"))
      battery_time *= 60;

   if (battery_flag == 0xFF) /* unknown state */
      *state = FRONTEND_POWERSTATE_NONE;
   else if (battery_flag & (1 << 7))       /* no battery */
      *state = FRONTEND_POWERSTATE_NO_SOURCE;
   else if (battery_flag & (1 << 3))   /* charging */
      *state = FRONTEND_POWERSTATE_CHARGING;
   else if (ac_status == 1)
      *state = FRONTEND_POWERSTATE_CHARGED;        /* on AC, not charging. */
   else
      *state = FRONTEND_POWERSTATE_ON_POWER_SOURCE;

   if (battery_percent >= 0)         /* -1 == unknown */
      *percent = (battery_percent > 100) ? 100 : battery_percent; /* clamp between 0%, 100% */
   if (battery_time >= 0)            /* -1 == unknown */
      *seconds = battery_time;

   if (buf)
      free(buf);
   buf = NULL;

   return true;

error:
   if (buf)
      free(buf);
   buf = NULL;

   return false;
}