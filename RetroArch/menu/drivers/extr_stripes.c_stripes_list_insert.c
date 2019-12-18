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
struct TYPE_6__ {int /*<<< orphan*/  zoom; int /*<<< orphan*/  label_alpha; int /*<<< orphan*/  alpha; scalar_t__ x; int /*<<< orphan*/  y; scalar_t__ fullpath; } ;
typedef  TYPE_1__ stripes_node_t ;
struct TYPE_7__ {int /*<<< orphan*/  items_active_alpha; int /*<<< orphan*/  items_passive_zoom; int /*<<< orphan*/  items_passive_alpha; } ;
typedef  TYPE_2__ stripes_handle_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 scalar_t__ file_list_get_userdata_at_offset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  file_list_set_userdata (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 size_t menu_navigation_get_selection () ; 
 scalar_t__ strdup (char const*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 TYPE_1__* stripes_alloc_node () ; 
 int /*<<< orphan*/  stripes_item_y (TYPE_2__*,int,int) ; 

__attribute__((used)) static void stripes_list_insert(void *userdata,
      file_list_t *list,
      const char *path,
      const char *fullpath,
      const char *unused,
      size_t list_size,
      unsigned entry_type)
{
   int current            = 0;
   int i                  = (int)list_size;
   stripes_node_t *node       = NULL;
   stripes_handle_t *stripes      = (stripes_handle_t*)userdata;
   size_t selection       = menu_navigation_get_selection();

   if (!stripes || !list)
      return;

   node = (stripes_node_t*)file_list_get_userdata_at_offset(list, i);

   if (!node)
      node = stripes_alloc_node();

   if (!node)
   {
      RARCH_ERR("XMB node could not be allocated.\n");
      return;
   }

   current           = (int)selection;

   if (!string_is_empty(fullpath))
   {
      if (node->fullpath)
         free(node->fullpath);

      node->fullpath = strdup(fullpath);
   }

   node->alpha       = stripes->items_passive_alpha;
   node->zoom        = stripes->items_passive_zoom;
   node->label_alpha = node->alpha;
   node->y           = stripes_item_y(stripes, i, current);
   node->x           = 0;

   if (i == current)
   {
      node->alpha       = stripes->items_active_alpha;
      node->label_alpha = stripes->items_active_alpha;
      node->zoom        = stripes->items_active_alpha;
   }

   file_list_set_userdata(list, i, node);
}