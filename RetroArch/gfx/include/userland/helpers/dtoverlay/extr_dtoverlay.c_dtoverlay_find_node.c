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
 int fdt_path_offset_namelen (int /*<<< orphan*/ ,char const*,int) ; 
 int strlen (char const*) ; 

int dtoverlay_find_node(DTBLOB_T *dtb, const char *node_path, int path_len)
{
   if (!path_len)
      path_len = strlen(node_path);
   return fdt_path_offset_namelen(dtb->fdt, node_path, path_len);
}