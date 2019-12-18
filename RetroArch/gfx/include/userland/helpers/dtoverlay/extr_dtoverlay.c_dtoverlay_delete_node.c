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
 int /*<<< orphan*/  dtoverlay_debug (char*,int,char const*) ; 
 int fdt_del_node (int /*<<< orphan*/ ,int) ; 
 int fdt_path_offset_namelen (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char const*) ; 

int dtoverlay_delete_node(DTBLOB_T *dtb, const char *node_path, int path_len)
{
   int node_off = 0;
   if (!path_len)
      path_len = strlen(node_path);

   dtoverlay_debug("delete_node(%.*s)", path_len, node_path);
   node_off = fdt_path_offset_namelen(dtb->fdt, node_path, path_len);
   if (node_off < 0)
      return node_off;
   return fdt_del_node(dtb->fdt, node_off);
}