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
 int /*<<< orphan*/  dtoverlay_error (char*,char const*) ; 
 int fdt_setprop (int /*<<< orphan*/ ,int,char const*,void const*,int) ; 

int dtoverlay_set_property(DTBLOB_T *dtb, int pos,
                           const char *prop_name, const void *prop, int prop_len)
{
   int err = fdt_setprop(dtb->fdt, pos, prop_name, prop, prop_len);
   if (err < 0)
      dtoverlay_error("Failed to set property '%s'", prop_name);
   return err;
}