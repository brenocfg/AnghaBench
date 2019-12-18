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
 char* fdt_getprop (int /*<<< orphan*/ ,int,char const*,int*) ; 
 int fdt_path_offset (int /*<<< orphan*/ ,char*) ; 

const char *dtoverlay_get_alias(DTBLOB_T *dtb, const char *alias_name)
{
   int node_off;
   int prop_len;
   const char *alias;

   node_off = fdt_path_offset(dtb->fdt, "/aliases");

   alias = fdt_getprop(dtb->fdt, node_off, alias_name, &prop_len);
   if (alias && !prop_len)
       alias = "";
   return alias;
}