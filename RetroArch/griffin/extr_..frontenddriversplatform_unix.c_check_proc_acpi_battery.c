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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
#define  ACPI_VAL_CHARGING_DISCHARGING 128 
 int djb2_calculate (char*) ; 
 int /*<<< orphan*/  filestream_exists (char*) ; 
 int /*<<< orphan*/  filestream_read_file (char*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ make_proc_acpi_key_val (char**,char**,char**) ; 
 char* proc_acpi_battery_path ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*,char*) ; 
 scalar_t__ string_is_equal (char*,char*) ; 
 scalar_t__ strtol (char*,char**,int) ; 

__attribute__((used)) static void check_proc_acpi_battery(const char * node, bool * have_battery,
      bool * charging, int *seconds, int *percent)
{
   char path[1024];
   const char *base  = proc_acpi_battery_path;
   int64_t length    = 0;
   char         *ptr = NULL;
   char  *buf        = NULL;
   char  *buf_info   = NULL;
   char         *key = NULL;
   char         *val = NULL;
   bool       charge = false;
   bool       choose = false;
   int       maximum = -1;
   int     remaining = -1;
   int          secs = -1;
   int           pct = -1;

   path[0]           = '\0';

   snprintf(path, sizeof(path), "%s/%s/%s", base, node, "state");

   if (!filestream_exists(path))
      goto end;

   if (!filestream_read_file(path, (void**)&buf, &length))
      goto end;

   snprintf(path, sizeof(path), "%s/%s/%s", base, node, "info");
   if (!filestream_read_file(path, (void**)&buf_info, &length))
      goto end;

   ptr = &buf[0];

   while (make_proc_acpi_key_val(&ptr, &key, &val))
   {
      if (string_is_equal(key, "present"))
      {
         if (string_is_equal(val, "yes"))
            *have_battery = true;
      }
      else if (string_is_equal(key, "charging state"))
      {
         if (string_is_equal(val, "charging"))
            charge = true;
         else
         {
            uint32_t val_hash = djb2_calculate(val);

            switch (val_hash)
            {
               case ACPI_VAL_CHARGING_DISCHARGING:
                  charge = true;
                  break;
               default:
                  break;
            }
         }
      }
      else if (string_is_equal(key, "remaining capacity"))
      {
         char *endptr = NULL;

         if (endptr && *endptr == ' ')
            remaining = (int)strtol(val, &endptr, 10);
      }
   }

   ptr = &buf_info[0];

   while (make_proc_acpi_key_val(&ptr, &key, &val))
   {
      char      *endptr = NULL;

      if (string_is_equal(key, "design capacity"))
         if (endptr && *endptr == ' ')
            maximum = (int)strtol(val, &endptr, 10);
   }

   if ((maximum >= 0) && (remaining >= 0))
   {
      pct = (int) ((((float) remaining) / ((float) maximum)) * 100.0f);
      if (pct < 0)
         pct = 0;
      if (pct > 100)
         pct = 100;
   }

   /* !!! FIXME: calculate (secs). */

   /*
    * We pick the battery that claims to have the most minutes left.
    *  (failing a report of minutes, we'll take the highest percent.)
    */
   if ((secs < 0) && (*seconds < 0))
   {
      if ((pct < 0) && (*percent < 0))
         choose = true;  /* at least we know there's a battery. */
      if (pct > *percent)
         choose = true;
   }
   else if (secs > *seconds)
      choose = true;

   if (choose)
   {
      *seconds  = secs;
      *percent  = pct;
      *charging = charge;
   }

end:
   if (buf_info)
      free(buf_info);
   if (buf)
      free(buf);
   buf      = NULL;
   buf_info = NULL;
}