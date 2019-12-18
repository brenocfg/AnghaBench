#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {scalar_t__ categories_selection_ptr; scalar_t__ categories_selection_ptr_old; int categories_active_idx; float categories_passive_width; unsigned int categories_active_idx_old; int /*<<< orphan*/  selection_ptr_old; int /*<<< orphan*/  selection_buf_old; int /*<<< orphan*/  categories_x_pos; } ;
typedef  TYPE_2__ stripes_handle_t ;
struct TYPE_17__ {scalar_t__ menu_horizontal_animation; } ;
struct TYPE_19__ {TYPE_1__ bools; } ;
typedef  TYPE_3__ settings_t ;
struct TYPE_20__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_4__ menu_entry_t ;
struct TYPE_21__ {float target_value; int tag; int /*<<< orphan*/ * subject; int /*<<< orphan*/ * cb; int /*<<< orphan*/  easing_enum; int /*<<< orphan*/  duration; } ;
typedef  TYPE_5__ menu_animation_ctx_entry_t ;
typedef  int /*<<< orphan*/  file_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  EASING_OUT_QUAD ; 
 int /*<<< orphan*/  MENU_ENUM_LABEL_VALUE_OFF ; 
 int /*<<< orphan*/  STRIPES_DELAY ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  menu_animation_push (TYPE_5__*) ; 
 int /*<<< orphan*/ * menu_entries_get_selection_buf_ptr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_entry_get (TYPE_4__*,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  menu_entry_init (TYPE_4__*) ; 
 size_t menu_navigation_get_selection () ; 
 int /*<<< orphan*/  msg_hash_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_empty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  string_is_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripes_list_switch_horizontal_list (TYPE_2__*) ; 
 int /*<<< orphan*/  stripes_list_switch_new (TYPE_2__*,int /*<<< orphan*/ *,int,size_t) ; 
 int /*<<< orphan*/  stripes_list_switch_old (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripes_set_thumbnail_content (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stripes_thumbnails_ident (char) ; 
 int /*<<< orphan*/  stripes_update_thumbnail_image (TYPE_2__*) ; 
 int /*<<< orphan*/  stripes_update_thumbnail_path (TYPE_2__*,int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void stripes_list_switch(stripes_handle_t *stripes)
{
   menu_animation_ctx_entry_t anim_entry;
   int dir                    = -1;
   file_list_t *selection_buf = menu_entries_get_selection_buf_ptr(0);
   size_t selection           = menu_navigation_get_selection();
   settings_t *settings = config_get_ptr();

   if (stripes->categories_selection_ptr > stripes->categories_selection_ptr_old)
      dir = 1;

   stripes->categories_active_idx += dir;

   stripes_list_switch_horizontal_list(stripes);

   anim_entry.duration     = STRIPES_DELAY;
   anim_entry.target_value = stripes->categories_passive_width
      * -(float)stripes->categories_selection_ptr;
   anim_entry.subject      = &stripes->categories_x_pos;
   anim_entry.easing_enum  = EASING_OUT_QUAD;
   /* TODO/FIXME - integer conversion resulted in change of sign */
   anim_entry.tag          = -1;
   anim_entry.cb           = NULL;

   if (anim_entry.subject)
      menu_animation_push(&anim_entry);

   dir = -1;
   if (stripes->categories_selection_ptr > stripes->categories_selection_ptr_old)
      dir = 1;

   stripes_list_switch_old(stripes, stripes->selection_buf_old,
         dir, stripes->selection_ptr_old);

   /* Check if we are to have horizontal animations. */
   if (settings->bools.menu_horizontal_animation)
      stripes_list_switch_new(stripes, selection_buf, dir, selection);
   stripes->categories_active_idx_old = (unsigned)stripes->categories_selection_ptr;

   if (!string_is_equal(stripes_thumbnails_ident('R'),
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_OFF)))
   {
      menu_entry_t entry;

      menu_entry_init(&entry);
      menu_entry_get(&entry, 0, selection, NULL, true);

      if (!string_is_empty(entry.path))
         stripes_set_thumbnail_content(stripes, entry.path, 0 /* will be ignored */);

      stripes_update_thumbnail_path(stripes, 0, 'R');
      stripes_update_thumbnail_image(stripes);
   }
   if (!string_is_equal(stripes_thumbnails_ident('L'),
            msg_hash_to_str(MENU_ENUM_LABEL_VALUE_OFF)))
   {
      menu_entry_t entry;

      menu_entry_init(&entry);
      menu_entry_get(&entry, 0, selection, NULL, true);

      if (!string_is_empty(entry.path))
         stripes_set_thumbnail_content(stripes, entry.path, 0 /* will be ignored */);

      stripes_update_thumbnail_path(stripes, 0, 'L');
      stripes_update_thumbnail_image(stripes);
   }
}