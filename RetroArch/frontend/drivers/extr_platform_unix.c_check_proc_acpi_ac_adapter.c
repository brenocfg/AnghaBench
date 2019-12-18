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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  path ;
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 scalar_t__ ACPI_VAL_ONLINE ; 
 scalar_t__ djb2_calculate (char*) ; 
 int /*<<< orphan*/  filestream_exists (char*) ; 
 int filestream_read_file (char*,void**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ make_proc_acpi_key_val (char**,char**,char**) ; 
 char* proc_acpi_ac_adapter_path ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*,char*) ; 
 scalar_t__ string_is_equal (char*,char*) ; 

__attribute__((used)) static void check_proc_acpi_ac_adapter(const char * node, bool *have_ac)
{
   char path[1024];
   const char *base = proc_acpi_ac_adapter_path;
   char       *buf  = NULL;
   char        *ptr = NULL;
   char        *key = NULL;
   char        *val = NULL;
   int64_t length   = 0;

   path[0]          = '\0';

   snprintf(path, sizeof(path), "%s/%s/%s", base, node, "state");
   if (!filestream_exists(path))
      return;

   if (filestream_read_file(path, (void**)&buf, &length) != 1)
      return;

   ptr = &buf[0];
   while (make_proc_acpi_key_val(&ptr, &key, &val))
   {
      uint32_t val_hash = djb2_calculate(val);

      if (string_is_equal(key, "state") &&
            val_hash == ACPI_VAL_ONLINE)
         *have_ac = true;
   }

   if (buf)
      free(buf);
   buf = NULL;
}