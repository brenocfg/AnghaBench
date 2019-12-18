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
 int /*<<< orphan*/  filestream_exists (char*) ; 
 int filestream_read_file (char*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* proc_acpi_sysfs_ac_adapter_path ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char*) ; 
 scalar_t__ strstr (char*,char*) ; 

__attribute__((used)) static void check_proc_acpi_sysfs_ac_adapter(const char * node, bool *have_ac)
{
   char  path[1024];
   int64_t length   = 0;
   char     *buf    = NULL;
   const char *base = proc_acpi_sysfs_ac_adapter_path;

   path[0]          = '\0';

   snprintf(path, sizeof(path), "%s/%s", base, "online");
   if (!filestream_exists(path))
      return;

   if (filestream_read_file(path, (void**)&buf, &length) != 1)
      return;

   if (strstr((char*)buf, "1"))
      *have_ac = true;

   free(buf);
}