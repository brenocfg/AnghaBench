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
 int fdt_add_subnode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int fdt_path_offset (int /*<<< orphan*/ ,char*) ; 
 int fdt_setprop_string (int /*<<< orphan*/ ,int,char const*,char const*) ; 

int dtoverlay_set_alias(DTBLOB_T *dtb, const char *alias_name, const char *value)
{
   int node_off;

   node_off = fdt_path_offset(dtb->fdt, "/aliases");
   if (node_off < 0)
       node_off = fdt_add_subnode(dtb->fdt, 0, "aliases");

   return fdt_setprop_string(dtb->fdt, node_off, alias_name, value);
}