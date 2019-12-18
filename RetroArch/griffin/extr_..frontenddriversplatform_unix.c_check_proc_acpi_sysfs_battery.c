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
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 unsigned int atoi (char*) ; 
 int /*<<< orphan*/  filestream_exists (char*) ; 
 int filestream_read_file (char*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* proc_acpi_sysfs_battery_path ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*,char*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static void check_proc_acpi_sysfs_battery(const char *node,
      bool *have_battery, bool *charging,
      int *seconds, int *percent)
{
   char path[1024];
   const char *base  = proc_acpi_sysfs_battery_path;
   char        *buf  = NULL;
   char         *ptr = NULL;
   char         *key = NULL;
   char         *val = NULL;
   bool       charge = false;
   bool       choose = false;
   unsigned capacity = 0;
   int64_t length    = 0;
   int       maximum = -1;
   int     remaining = -1;
   int          secs = -1;
   int           pct = -1;

   path[0]           = '\0';

   snprintf(path, sizeof(path), "%s/%s/%s", base, node, "status");

   if (!filestream_exists(path))
      return;

   if (filestream_read_file(path, (void**)&buf, &length) != 1)
      return;

   if (buf)
   {
      if (strstr((char*)buf, "Discharging"))
         *have_battery = true;
      else if (strstr((char*)buf, "Charging"))
      {
         *have_battery = true;
         *charging = true;
      }
      else if (strstr((char*)buf, "Full"))
         *have_battery = true;
      free(buf);
   }

   buf = NULL;

   snprintf(path, sizeof(path), "%s/%s/%s", base, node, "capacity");
   if (filestream_read_file(path, (void**)&buf, &length) != 1)
      goto end;

   capacity = atoi(buf);

   *percent = capacity;

end:
   free(buf);
   buf = NULL;
}