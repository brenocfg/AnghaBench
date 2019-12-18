#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int on_sys_bar; int on_header; int list_text; int list_text_highlighted; int list_hint_text; int list_hint_text_highlighted; int sys_bar_background; int title_bar_background; int list_background; int list_highlighted_background; int nav_bar_background; int surface_background; int thumbnail_background; int list_icon; int list_switch_on; int list_switch_on_background; int list_switch_off; int list_switch_off_background; int nav_bar_icon_active; int nav_bar_icon_passive; int nav_bar_icon_disabled; int header_shadow; int landscape_border_shadow; int scrollbar; int divider; int screen_fade; float screen_fade_opacity; int missing_thumbnail_icon; int /*<<< orphan*/  landscape_border_shadow_opacity; int /*<<< orphan*/  header_shadow_opacity; } ;
typedef  TYPE_2__ materialui_theme_t ;
struct TYPE_6__ {int sys_bar_text; int header_text; int list_text; int list_text_highlighted; int list_hint_text; int list_hint_text_highlighted; int /*<<< orphan*/  landscape_border_shadow_opacity; int /*<<< orphan*/ * landscape_border_shadow_right; int /*<<< orphan*/ * landscape_border_shadow_left; int /*<<< orphan*/ * header_shadow; int /*<<< orphan*/ * missing_thumbnail_icon; int /*<<< orphan*/ * screen_fade; int /*<<< orphan*/ * divider; int /*<<< orphan*/ * scrollbar; int /*<<< orphan*/ * nav_bar_icon_disabled; int /*<<< orphan*/ * nav_bar_icon_passive; int /*<<< orphan*/ * nav_bar_icon_active; int /*<<< orphan*/ * list_switch_off_background; int /*<<< orphan*/ * list_switch_off; int /*<<< orphan*/ * list_switch_on_background; int /*<<< orphan*/ * list_switch_on; int /*<<< orphan*/ * list_icon; int /*<<< orphan*/ * header_icon; int /*<<< orphan*/ * sys_bar_icon; int /*<<< orphan*/ * thumbnail_background; int /*<<< orphan*/ * surface_background; int /*<<< orphan*/ * nav_bar_background; int /*<<< orphan*/ * list_highlighted_background; int /*<<< orphan*/ * list_background; int /*<<< orphan*/ * title_bar_background; int /*<<< orphan*/ * sys_bar_background; } ;
struct TYPE_8__ {TYPE_1__ colors; } ;
typedef  TYPE_3__ materialui_handle_t ;
typedef  enum materialui_color_theme { ____Placeholder_materialui_color_theme } materialui_color_theme ;

/* Variables and functions */
 int /*<<< orphan*/  hex32_to_rgba_normalized (int,int /*<<< orphan*/ *,float) ; 
 TYPE_2__* materialui_get_theme (int) ; 

__attribute__((used)) static void materialui_prepare_colors(
      materialui_handle_t *mui, enum materialui_color_theme color_theme)
{
   const materialui_theme_t *current_theme = materialui_get_theme(color_theme);

   /* Parse theme colours */

   /* > Text (& small inline icon) colours */
   mui->colors.sys_bar_text               = (current_theme->on_sys_bar                 << 8) | 0xFF;
   mui->colors.header_text                = (current_theme->on_header                  << 8) | 0xFF;
   mui->colors.list_text                  = (current_theme->list_text                  << 8) | 0xFF;
   mui->colors.list_text_highlighted      = (current_theme->list_text_highlighted      << 8) | 0xFF;
   mui->colors.list_hint_text             = (current_theme->list_hint_text             << 8) | 0xFF;
   mui->colors.list_hint_text_highlighted = (current_theme->list_hint_text_highlighted << 8) | 0xFF;

   /* > Background colours */
   hex32_to_rgba_normalized(
            current_theme->sys_bar_background,
            mui->colors.sys_bar_background, 1.0f);
   hex32_to_rgba_normalized(
            current_theme->title_bar_background,
            mui->colors.title_bar_background, 1.0f);
   hex32_to_rgba_normalized(
            current_theme->list_background,
            mui->colors.list_background, 1.0f);
   hex32_to_rgba_normalized(
            current_theme->list_highlighted_background,
            mui->colors.list_highlighted_background, 1.0f);
   hex32_to_rgba_normalized(
            current_theme->nav_bar_background,
            mui->colors.nav_bar_background, 1.0f);
   hex32_to_rgba_normalized(
            current_theme->surface_background,
            mui->colors.surface_background, 1.0f);
   hex32_to_rgba_normalized(
            current_theme->thumbnail_background,
            mui->colors.thumbnail_background, 1.0f);

   /* > System bar + header icon colours */
   hex32_to_rgba_normalized(
            current_theme->on_sys_bar,
            mui->colors.sys_bar_icon, 1.0f);
   hex32_to_rgba_normalized(
            current_theme->on_header,
            mui->colors.header_icon, 1.0f);

   /* > List icon colours */
   hex32_to_rgba_normalized(
            current_theme->list_icon,
            mui->colors.list_icon, 1.0f);
   hex32_to_rgba_normalized(
            current_theme->list_switch_on,
            mui->colors.list_switch_on, 1.0f);
   hex32_to_rgba_normalized(
            current_theme->list_switch_on_background,
            mui->colors.list_switch_on_background, 1.0f);
   hex32_to_rgba_normalized(
            current_theme->list_switch_off,
            mui->colors.list_switch_off, 1.0f);
   hex32_to_rgba_normalized(
            current_theme->list_switch_off_background,
            mui->colors.list_switch_off_background, 1.0f);

   /* > Navigation bar icon colours */
   hex32_to_rgba_normalized(
            current_theme->nav_bar_icon_active,
            mui->colors.nav_bar_icon_active, 1.0f);
   hex32_to_rgba_normalized(
            current_theme->nav_bar_icon_passive,
            mui->colors.nav_bar_icon_passive, 1.0f);
   hex32_to_rgba_normalized(
            current_theme->nav_bar_icon_disabled,
            mui->colors.nav_bar_icon_disabled, 1.0f);

   /* > Misc. colours */
   hex32_to_rgba_normalized(
            current_theme->header_shadow,
            mui->colors.header_shadow, 0.0f);
   hex32_to_rgba_normalized(
            current_theme->landscape_border_shadow,
            mui->colors.landscape_border_shadow_left, 0.0f);
   hex32_to_rgba_normalized(
            current_theme->landscape_border_shadow,
            mui->colors.landscape_border_shadow_right, 0.0f);
   hex32_to_rgba_normalized(
            current_theme->scrollbar,
            mui->colors.scrollbar, 1.0f);
   hex32_to_rgba_normalized(
            current_theme->divider,
            mui->colors.divider, 1.0f);
   hex32_to_rgba_normalized(
            current_theme->screen_fade,
            mui->colors.screen_fade, current_theme->screen_fade_opacity);
   hex32_to_rgba_normalized(
            current_theme->missing_thumbnail_icon,
            mui->colors.missing_thumbnail_icon, 1.0f);

   /* Shadow colours require special handling
    * (since they are gradients) */
   mui->colors.header_shadow[11]                 = current_theme->header_shadow_opacity;
   mui->colors.header_shadow[15]                 = current_theme->header_shadow_opacity;
   mui->colors.landscape_border_shadow_left[7]   = current_theme->landscape_border_shadow_opacity;
   mui->colors.landscape_border_shadow_left[15]  = current_theme->landscape_border_shadow_opacity;
   mui->colors.landscape_border_shadow_right[3]  = current_theme->landscape_border_shadow_opacity;
   mui->colors.landscape_border_shadow_right[11] = current_theme->landscape_border_shadow_opacity;
   mui->colors.landscape_border_shadow_opacity   = current_theme->landscape_border_shadow_opacity;
}