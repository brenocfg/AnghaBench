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
struct fdt_property {char* data; } ;
struct TYPE_7__ {int /*<<< orphan*/  fdt; } ;
struct TYPE_6__ {char* param; int /*<<< orphan*/  len; int /*<<< orphan*/  b; } ;
typedef  TYPE_1__ DTOVERLAY_PARAM_T ;
typedef  TYPE_2__ DTBLOB_T ;

/* Variables and functions */
 int /*<<< orphan*/  FDT_ERR_BADPATH ; 
 int NON_FATAL (int /*<<< orphan*/ ) ; 
 int dtoverlay_create_node (TYPE_2__*,char const*,int) ; 
 int fdt_appendprop (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct fdt_property* fdt_get_property_w (int /*<<< orphan*/ ,int,char const*,int*) ; 
 int fdt_setprop (int /*<<< orphan*/ ,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strrchr (char const*,char) ; 

int dtoverlay_merge_params(DTBLOB_T *dtb, const DTOVERLAY_PARAM_T *params,
                           unsigned int num_params)
{
   int err = 0;
   unsigned int i;

   for (i=0; (i<num_params) && (err == 0); i++) {
      const DTOVERLAY_PARAM_T *p;
      const char *node_name, *slash;
      int node_off, path_len;

      p = params + i;
      node_name = p->param;
      slash = strrchr(node_name, '/');

      if (!slash)
      {
         err = NON_FATAL(FDT_ERR_BADPATH);
         break;
      }

      // Ensure that root properties ("/xxx") work
      if (slash == node_name)
         path_len = 1;
      else
         path_len = slash - node_name;

      // find node, create if it does not exist yet
      node_off = dtoverlay_create_node(dtb, node_name, path_len);
      if (node_off >= 0)
      {
         const char *prop_name = slash + 1;
         int prop_len;
         struct fdt_property *prop;

         if ((strcmp(prop_name, "bootargs") == 0) &&
            ((prop = fdt_get_property_w(dtb->fdt, node_off, prop_name, &prop_len)) != NULL) &&
            (prop_len > 0) && *prop->data)
         {
            prop->data[prop_len - 1] = ' ';
            err = fdt_appendprop(dtb->fdt, node_off, prop_name, p->b, p->len);
         }
         else
            err = fdt_setprop(dtb->fdt, node_off, prop_name, p->b, p->len);
      }
      else
         err = node_off;
   }

   return err;
}