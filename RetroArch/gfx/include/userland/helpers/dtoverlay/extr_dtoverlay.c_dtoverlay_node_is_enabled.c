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
typedef  int /*<<< orphan*/  DTBLOB_T ;

/* Variables and functions */
 void* dtoverlay_get_property (int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char*) ; 

int dtoverlay_node_is_enabled(DTBLOB_T *dtb, int pos)
{
   if (pos >= 0)
   {
      const void *prop = dtoverlay_get_property(dtb, pos, "status", NULL);
      if (prop &&
          ((strcmp((const char *)prop, "okay") == 0) ||
           (strcmp((const char *)prop, "ok") == 0)))
         return 1;
   }
   return 0;
}