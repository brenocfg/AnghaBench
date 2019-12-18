#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int depth; int old_depth; int icon_size; int /*<<< orphan*/  textures_arrow_alpha; int /*<<< orphan*/  x; int /*<<< orphan*/  selection_ptr_old; int /*<<< orphan*/  selection_buf_old; } ;
typedef  TYPE_1__ stripes_handle_t ;
struct TYPE_10__ {int target_value; int tag; int /*<<< orphan*/ * subject; int /*<<< orphan*/ * cb; int /*<<< orphan*/  easing_enum; int /*<<< orphan*/  duration; } ;
typedef  TYPE_2__ menu_animation_ctx_entry_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  EASING_OUT_QUAD ; 
 int /*<<< orphan*/  MENU_LIST_PLAIN ; 
 int /*<<< orphan*/  STRIPES_DELAY ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_2__*) ; 
 int /*<<< orphan*/ * menu_entries_get_selection_buf_ptr (int /*<<< orphan*/ ) ; 
 size_t menu_navigation_get_selection () ; 
 scalar_t__ stripes_list_get_size (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripes_list_open_horizontal_list (TYPE_1__*) ; 
 int /*<<< orphan*/  stripes_list_open_new (TYPE_1__*,int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  stripes_list_open_old (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void stripes_list_open(stripes_handle_t *stripes)
{
   menu_animation_ctx_entry_t entry;

   int                    dir = 0;
   file_list_t *selection_buf = menu_entries_get_selection_buf_ptr(0);
   size_t selection           = menu_navigation_get_selection();

   stripes->depth = (int)stripes_list_get_size(stripes, MENU_LIST_PLAIN);

   if (stripes->depth > stripes->old_depth)
      dir = 1;
   else if (stripes->depth < stripes->old_depth)
      dir = -1;

   stripes_list_open_horizontal_list(stripes);

   stripes_list_open_old(stripes, stripes->selection_buf_old,
         dir, stripes->selection_ptr_old);
   stripes_list_open_new(stripes, selection_buf,
         dir, selection);

   entry.duration     = STRIPES_DELAY;
   entry.target_value = stripes->icon_size * -(stripes->depth*2-2);
   entry.subject      = &stripes->x;
   entry.easing_enum  = EASING_OUT_QUAD;
   /* TODO/FIXME - integer conversion resulted in change of sign */
   entry.tag          = -1;
   entry.cb           = NULL;

   switch (stripes->depth)
   {
      case 1:
         menu_animation_push(&entry);

         entry.target_value = 0;
         entry.subject      = &stripes->textures_arrow_alpha;

         menu_animation_push(&entry);
         break;
      case 2:
         menu_animation_push(&entry);

         entry.target_value = 1;
         entry.subject      = &stripes->textures_arrow_alpha;

         menu_animation_push(&entry);
         break;
   }

   stripes->old_depth = stripes->depth;
}