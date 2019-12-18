#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  zoom; int /*<<< orphan*/  alpha; } ;
typedef  TYPE_2__ xmb_node_t ;
struct TYPE_14__ {size_t system_tab_end; float categories_passive_alpha; float categories_passive_zoom; unsigned int categories_active_idx; float categories_active_alpha; float categories_active_zoom; } ;
typedef  TYPE_3__ xmb_handle_t ;
struct TYPE_12__ {int menu_xmb_animation_horizontal_highlight; } ;
struct TYPE_15__ {TYPE_1__ uints; } ;
typedef  TYPE_4__ settings_t ;
struct TYPE_16__ {float target_value; int tag; int duration; int /*<<< orphan*/ * subject; int /*<<< orphan*/  easing_enum; int /*<<< orphan*/ * cb; } ;
typedef  TYPE_5__ menu_animation_ctx_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  EASING_IN_SINE ; 
 int /*<<< orphan*/  EASING_OUT_BOUNCE ; 
 int /*<<< orphan*/  EASING_OUT_QUAD ; 
 int /*<<< orphan*/  MENU_LIST_HORIZONTAL ; 
 int XMB_DELAY ; 
 TYPE_4__* config_get_ptr () ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_5__*) ; 
 TYPE_2__* xmb_get_node (TYPE_3__*,unsigned int) ; 
 size_t xmb_list_get_size (TYPE_3__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xmb_list_switch_horizontal_list(xmb_handle_t *xmb)
{
   unsigned j;
   size_t list_size = xmb_list_get_size(xmb, MENU_LIST_HORIZONTAL)
      + xmb->system_tab_end;

   for (j = 0; j <= list_size; j++)
   {
      menu_animation_ctx_entry_t entry;
      settings_t *settings        = config_get_ptr();
      float ia                    = xmb->categories_passive_alpha;
      float iz                    = xmb->categories_passive_zoom;
      xmb_node_t *node            = xmb_get_node(xmb, j);

      if (!node)
         continue;

      if (j == xmb->categories_active_idx)
      {
         ia = xmb->categories_active_alpha;
         iz = xmb->categories_active_zoom;
      }

      /* Horizontal icon animation */

      entry.target_value = ia;
      entry.subject      = &node->alpha;
      /* TODO/FIXME - integer conversion resulted in change of sign */
      entry.tag          = -1;
      entry.cb           = NULL;

      switch (settings->uints.menu_xmb_animation_horizontal_highlight)
      {
         case 0:
            entry.duration     = XMB_DELAY;
            entry.easing_enum  = EASING_OUT_QUAD;
            break;
         case 1:
            entry.duration     = XMB_DELAY + (XMB_DELAY / 2);
            entry.easing_enum  = EASING_IN_SINE;
            break;
         case 2:
            entry.duration     = XMB_DELAY * 2;
            entry.easing_enum  = EASING_OUT_BOUNCE;
            break;
      }

      menu_animation_push(&entry);

      entry.target_value = iz;
      entry.subject      = &node->zoom;

      menu_animation_push(&entry);
   }
}