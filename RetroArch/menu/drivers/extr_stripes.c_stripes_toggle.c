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
struct TYPE_6__ {int depth; scalar_t__ alpha; } ;
typedef  TYPE_1__ stripes_handle_t ;
struct TYPE_7__ {int duration; float target_value; int tag; int /*<<< orphan*/ * cb; int /*<<< orphan*/  easing_enum; scalar_t__* subject; } ;
typedef  TYPE_2__ menu_animation_ctx_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  EASING_OUT_QUAD ; 
 int /*<<< orphan*/  MENU_ENTRIES_CTL_NEEDS_REFRESH ; 
 int /*<<< orphan*/  MENU_LIST_PLAIN ; 
 int /*<<< orphan*/  RARCH_MENU_CTL_SET_PREVENT_POPULATE ; 
 int /*<<< orphan*/  RARCH_MENU_CTL_UNSET_PREVENT_POPULATE ; 
 int STRIPES_DELAY ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_2__*) ; 
 int /*<<< orphan*/  menu_driver_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  menu_entries_ctl (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stripes_list_get_size (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripes_toggle_horizontal_list (TYPE_1__*) ; 

__attribute__((used)) static void stripes_toggle(void *userdata, bool menu_on)
{
   menu_animation_ctx_entry_t entry;
   bool tmp             = false;
   stripes_handle_t *stripes    = (stripes_handle_t*)userdata;

   if (!stripes)
      return;

   stripes->depth         = (int)stripes_list_get_size(stripes, MENU_LIST_PLAIN);

   if (!menu_on)
   {
      stripes->alpha = 0;
      return;
   }

   entry.duration     = STRIPES_DELAY * 2;
   entry.target_value = 1.0f;
   entry.subject      = &stripes->alpha;
   entry.easing_enum  = EASING_OUT_QUAD;
   /* TODO/FIXME - integer conversion resulted in change of sign */
   entry.tag          = -1;
   entry.cb           = NULL;

   menu_animation_push(&entry);

   tmp = !menu_entries_ctl(MENU_ENTRIES_CTL_NEEDS_REFRESH, NULL);

   if (tmp)
      menu_driver_ctl(RARCH_MENU_CTL_SET_PREVENT_POPULATE, NULL);
   else
      menu_driver_ctl(RARCH_MENU_CTL_UNSET_PREVENT_POPULATE, NULL);

   stripes_toggle_horizontal_list(stripes);
}