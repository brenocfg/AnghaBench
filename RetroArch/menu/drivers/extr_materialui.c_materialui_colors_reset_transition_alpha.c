#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int list_text; int list_text_highlighted; int list_hint_text; int list_hint_text_highlighted; float landscape_border_shadow_opacity; float* landscape_border_shadow_left; float* landscape_border_shadow_right; int /*<<< orphan*/  missing_thumbnail_icon; int /*<<< orphan*/  surface_background; int /*<<< orphan*/  scrollbar; int /*<<< orphan*/  list_switch_off_background; int /*<<< orphan*/  list_switch_off; int /*<<< orphan*/  list_switch_on_background; int /*<<< orphan*/  list_switch_on; int /*<<< orphan*/  list_icon; int /*<<< orphan*/  list_highlighted_background; } ;
struct TYPE_5__ {float transition_alpha; scalar_t__ landscape_entry_margin; float transition_x_offset; TYPE_1__ colors; } ;
typedef  TYPE_2__ materialui_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  menu_display_set_alpha (int /*<<< orphan*/ ,float) ; 

__attribute__((used)) static void materialui_colors_reset_transition_alpha(materialui_handle_t *mui)
{
   if (mui->transition_alpha < 1.0f)
   {
      /* Text colours */
      mui->colors.list_text                  = (mui->colors.list_text                  | 0xFF);
      mui->colors.list_text_highlighted      = (mui->colors.list_text_highlighted      | 0xFF);
      mui->colors.list_hint_text             = (mui->colors.list_hint_text             | 0xFF);
      mui->colors.list_hint_text_highlighted = (mui->colors.list_hint_text_highlighted | 0xFF);

      /* Background/object colours */
      menu_display_set_alpha(mui->colors.list_highlighted_background, 1.0f);
      menu_display_set_alpha(mui->colors.list_icon,                   1.0f);
      menu_display_set_alpha(mui->colors.list_switch_on,              1.0f);
      menu_display_set_alpha(mui->colors.list_switch_on_background,   1.0f);
      menu_display_set_alpha(mui->colors.list_switch_off,             1.0f);
      menu_display_set_alpha(mui->colors.list_switch_off_background,  1.0f);
      menu_display_set_alpha(mui->colors.scrollbar,                   1.0f);
      menu_display_set_alpha(mui->colors.surface_background,          1.0f);
      menu_display_set_alpha(mui->colors.missing_thumbnail_icon,      1.0f);

      /* Landscape border shadow only fades if:
       * - Landscape border is shown
       * - We are currently performing a slide animation */
      if ((mui->landscape_entry_margin != 0) &&
          (mui->transition_x_offset != 0.0f))
      {
         float border_shadow_alpha =
               mui->colors.landscape_border_shadow_opacity;

         mui->colors.landscape_border_shadow_left[7]   = border_shadow_alpha;
         mui->colors.landscape_border_shadow_left[15]  = border_shadow_alpha;
         mui->colors.landscape_border_shadow_right[3]  = border_shadow_alpha;
         mui->colors.landscape_border_shadow_right[11] = border_shadow_alpha;
      }
   }
}