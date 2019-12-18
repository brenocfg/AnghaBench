#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  fdt; } ;
struct TYPE_6__ {int /*<<< orphan*/  len; int /*<<< orphan*/  b; int /*<<< orphan*/  param; } ;
typedef  TYPE_1__ DTOVERLAY_PARAM_T ;
typedef  TYPE_2__ DTBLOB_T ;

/* Variables and functions */
 int dtoverlay_create_node (TYPE_2__*,char const*,int /*<<< orphan*/ ) ; 
 int fdt_path_offset (int /*<<< orphan*/ ,char const*) ; 
 int fdt_setprop (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int dtoverlay_set_node_properties(DTBLOB_T *dtb, const char *node_path,
                                  DTOVERLAY_PARAM_T *properties,
                                  unsigned int num_properties)
{
   int err = 0;
   int node_off;

   node_off = fdt_path_offset(dtb->fdt, node_path);
   if (node_off < 0)
      node_off = dtoverlay_create_node(dtb, node_path, 0);
   if (node_off >= 0)
   {
      int i;
      for (i = 0; (i < num_properties) && (err == 0); i++)
      {
         DTOVERLAY_PARAM_T *p;

         p = properties + i;
         err = fdt_setprop(dtb->fdt, node_off, p->param, p->b, p->len);
      }
   }
   else
      err = node_off;
   return err;
}