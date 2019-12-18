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
struct TYPE_7__ {double above_subitem_offset; double above_item_offset; double active_item_factor; double under_item_offset; double categories_active_zoom; double categories_passive_zoom; int categories_angle; int categories_active_y; int categories_before_y; int categories_after_y; int categories_active_x; int categories_before_x; int categories_after_x; int categories_passive_width; int categories_active_width; double items_active_zoom; double items_passive_zoom; double categories_active_alpha; double categories_passive_alpha; double items_active_alpha; double items_passive_alpha; double shadow_offset; double font2_size; double thumbnail_width; double left_thumbnail_width; double savestate_thumbnail_width; double cursor_size; double icon_spacing_horizontal; double icon_spacing_vertical; int margins_screen_top; double margins_screen_left; int margins_title_left; int margins_title_top; int margins_title_bottom; double margins_label_left; unsigned int margins_label_top; double margins_setting_left; int margins_dialog; int margins_slice; double icon_size; unsigned int font_size; } ;
typedef  TYPE_2__ stripes_handle_t ;
struct TYPE_6__ {int menu_scale_factor; } ;
struct TYPE_8__ {TYPE_1__ floats; } ;
typedef  TYPE_3__ settings_t ;

/* Variables and functions */
 int /*<<< orphan*/  RARCH_LOG (char*,double) ; 
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  menu_display_set_header_height (unsigned int) ; 
 double* stripes_scale_mod ; 

__attribute__((used)) static void stripes_layout_ps3(stripes_handle_t *stripes, int width, int height)
{
   unsigned new_font_size, new_header_height;
   settings_t *settings          = config_get_ptr();

   float scale_factor            =
      (settings->floats.menu_scale_factor * width) / 1920.0f;

   stripes->above_subitem_offset     =   1.5;
   stripes->above_item_offset        =  -1.0;
   stripes->active_item_factor       =   3.0;
   stripes->under_item_offset        =   5.0;

   stripes->categories_active_zoom   = 1.0;
   stripes->categories_passive_zoom  = 0.25;

   stripes->categories_angle         = 400 * scale_factor;

   stripes->categories_active_y      = height / 2;
   stripes->categories_before_y      = 64 * scale_factor;
   stripes->categories_after_y       = height - 64 * scale_factor;

   stripes->categories_active_x      = stripes->categories_angle / 2;
   stripes->categories_before_x      = stripes->categories_angle - 22 * scale_factor;
   stripes->categories_after_x       = 22 * scale_factor;

   stripes->categories_passive_width = 128 * scale_factor;
   stripes->categories_active_width  = 1200 * scale_factor;

   stripes->items_active_zoom        = 1.0;
   stripes->items_passive_zoom       = 0.5;

   stripes->categories_active_alpha  = 1.0;
   stripes->categories_passive_alpha = 1.0;
   stripes->items_active_alpha       = 1.0;
   stripes->items_passive_alpha      = 0.85;

   stripes->shadow_offset            = 2.0;

   new_font_size                 = 32.0  * scale_factor;
   stripes->font2_size               = 24.0  * scale_factor;
   new_header_height             = 128.0 * scale_factor;

   stripes->thumbnail_width          = 1024.0 * scale_factor;
   stripes->left_thumbnail_width     = 1024.0 * scale_factor;
   stripes->savestate_thumbnail_width= 460.0 * scale_factor;
   stripes->cursor_size              = 64.0 * scale_factor;

   stripes->icon_spacing_horizontal  = 200.0 * scale_factor;
   stripes->icon_spacing_vertical    = 64.0 * scale_factor;

   stripes->margins_screen_top       = (256+32) * scale_factor;
   stripes->margins_screen_left      = 336.0 * scale_factor;

   stripes->margins_title_left       = 60 * scale_factor;
   stripes->margins_title_top        = 60 * scale_factor + new_font_size / 3;
   stripes->margins_title_bottom     = 60 * scale_factor - new_font_size / 3;

   stripes->margins_label_left       = 85.0 * scale_factor;
   stripes->margins_label_top        = new_font_size / 3.0;

   stripes->margins_setting_left     = 600.0 * scale_factor * stripes_scale_mod[6];
   stripes->margins_dialog           = 48 * scale_factor;

   stripes->margins_slice            = 16;

   stripes->icon_size                = 256.0 * scale_factor;
   stripes->font_size                = new_font_size;

#ifdef STRIPES_DEBUG
   RARCH_LOG("[XMB] margin screen left: %.2f\n",  stripes->margins_screen_left);
   RARCH_LOG("[XMB] margin screen top:  %.2f\n",  stripes->margins_screen_top);
   RARCH_LOG("[XMB] margin title left:  %.2f\n",  stripes->margins_title_left);
   RARCH_LOG("[XMB] margin title top:   %.2f\n",  stripes->margins_title_top);
   RARCH_LOG("[XMB] margin title bott:  %.2f\n",  stripes->margins_title_bottom);
   RARCH_LOG("[XMB] margin label left:  %.2f\n",  stripes->margins_label_left);
   RARCH_LOG("[XMB] margin label top:   %.2f\n",  stripes->margins_label_top);
   RARCH_LOG("[XMB] margin sett left:   %.2f\n",  stripes->margins_setting_left);
   RARCH_LOG("[XMB] icon spacing hor:   %.2f\n",  stripes->icon_spacing_horizontal);
   RARCH_LOG("[XMB] icon spacing ver:   %.2f\n",  stripes->icon_spacing_vertical);
   RARCH_LOG("[XMB] icon size:          %.2f\n",  stripes->icon_size);
#endif

   menu_display_set_header_height(new_header_height);
}