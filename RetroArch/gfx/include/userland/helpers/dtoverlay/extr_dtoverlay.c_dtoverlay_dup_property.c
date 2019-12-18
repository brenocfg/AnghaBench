#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fdt; } ;
typedef  TYPE_1__ DTBLOB_T ;

/* Variables and functions */
 int /*<<< orphan*/  dtoverlay_debug (char*,char const*,char const*,char const*) ; 
 TYPE_1__* fdt_getprop (int /*<<< orphan*/ ,int,char const*,int*) ; 
 int fdt_path_offset (int /*<<< orphan*/ ,char const*) ; 
 int fdt_setprop (int /*<<< orphan*/ ,int,char const*,void*,int) ; 
 int fdt_setprop_inplace (int /*<<< orphan*/ ,int,char const*,TYPE_1__ const*,int) ; 
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (void*,TYPE_1__ const*,int) ; 

int dtoverlay_dup_property(DTBLOB_T *dtb, const char *node_name,
                           const char *dst, const char *src)
{
   /* Find the node and src property */
   const DTBLOB_T *src_prop;
   int node_off;
   int prop_len = 0;
   int err = 0;

   node_off = fdt_path_offset(dtb->fdt, node_name);
   if (node_off < 0)
      return 0;

   src_prop = fdt_getprop(dtb->fdt, node_off, src, &prop_len);
   if (!src_prop)
      return 0;

   err = fdt_setprop_inplace(dtb->fdt, node_off, dst, src_prop, prop_len);
   if (err != 0)
   {
      void *prop_data;
      /* Copy the src property, just in case things move */
      prop_data = malloc(prop_len);
      memcpy(prop_data, src_prop, prop_len);

      err = fdt_setprop(dtb->fdt, node_off, dst, prop_data, prop_len);

      free(prop_data);
   }

   if (err == 0)
      dtoverlay_debug("%s:%s=%s", node_name, dst, src);
   return err;
}