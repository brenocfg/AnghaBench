#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  fdt; } ;
typedef  TYPE_1__ DTBLOB_T ;

/* Variables and functions */
 int /*<<< orphan*/  dtoverlay_debug (char*,...) ; 
 char* fdt_getprop (int /*<<< orphan*/ ,int,char const*,int*) ; 
 int fdt_path_offset (int /*<<< orphan*/ ,char*) ; 

const char *dtoverlay_find_override(DTBLOB_T *dtb, const char *override_name,
                                    int *data_len)
{
   int overrides_off;
   const char *data;
   int len;

   // Find the table of overrides
   overrides_off = fdt_path_offset(dtb->fdt, "/__overrides__");

   if (overrides_off < 0)
   {
      dtoverlay_debug("/__overrides__ node not found");
      *data_len = overrides_off;
      return NULL;
   }

   // Locate the property
   data = fdt_getprop(dtb->fdt, overrides_off, override_name, &len);
   *data_len = len;
   if (data)
      dtoverlay_debug("Found override %s", override_name);
   else
      dtoverlay_debug("/__overrides__ has no %s property", override_name);

   return data;
}