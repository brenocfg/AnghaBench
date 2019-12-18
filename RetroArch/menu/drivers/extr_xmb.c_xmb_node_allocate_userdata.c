#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zoom; int /*<<< orphan*/  alpha; } ;
typedef  TYPE_1__ xmb_node_t ;
struct TYPE_9__ {unsigned int system_tab_end; unsigned int categories_active_idx; int /*<<< orphan*/  horizontal_list; int /*<<< orphan*/  categories_active_zoom; int /*<<< orphan*/  categories_active_alpha; int /*<<< orphan*/  categories_passive_zoom; int /*<<< orphan*/  categories_passive_alpha; } ;
typedef  TYPE_2__ xmb_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_ERR (char*) ; 
 scalar_t__ file_list_get_userdata_at_offset (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  file_list_set_userdata (int /*<<< orphan*/ ,unsigned int,TYPE_1__*) ; 
 TYPE_1__* xmb_alloc_node () ; 
 int /*<<< orphan*/  xmb_free_node (TYPE_1__*) ; 

__attribute__((used)) static xmb_node_t *xmb_node_allocate_userdata(
      xmb_handle_t *xmb, unsigned i)
{
   xmb_node_t *tmp  = NULL;
   xmb_node_t *node = xmb_alloc_node();

   if (!node)
   {
      RARCH_ERR("XMB node could not be allocated.\n");
      return NULL;
   }

   node->alpha = xmb->categories_passive_alpha;
   node->zoom  = xmb->categories_passive_zoom;

   if ((i + xmb->system_tab_end) == xmb->categories_active_idx)
   {
      node->alpha = xmb->categories_active_alpha;
      node->zoom  = xmb->categories_active_zoom;
   }

   tmp = (xmb_node_t*)file_list_get_userdata_at_offset(
         xmb->horizontal_list, i);
   xmb_free_node(tmp);

   file_list_set_userdata(xmb->horizontal_list, i, node);

   return node;
}