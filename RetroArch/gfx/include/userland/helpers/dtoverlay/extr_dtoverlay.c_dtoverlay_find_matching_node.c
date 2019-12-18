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
 char* fdt_get_name (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int fdt_next_node (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char const*,int) ; 

int dtoverlay_find_matching_node(DTBLOB_T *dtb, const char **node_names,
                                 int pos)
{
   while (1)
   {
      const char *node_name;
      pos = fdt_next_node(dtb->fdt, pos, NULL);
      if (pos < 0)
         break;
      node_name = fdt_get_name(dtb->fdt, pos, NULL);
      if (node_name)
      {
         int i;
         for (i = 0; node_names[i]; i++)
         {
            const char *node = node_names[i];
            int matchlen = strlen(node);
            if ((strncmp(node_name, node, matchlen) == 0) &&
                ((node[matchlen] == '\0') ||
                 (node[matchlen] == '@')))
               return pos;
         }
      }
   }
   return -1;
}