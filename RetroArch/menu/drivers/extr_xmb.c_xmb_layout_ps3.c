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
struct TYPE_7__ {double above_subitem_offset; double above_item_offset; double active_item_factor; double under_item_offset; double categories_active_zoom; double categories_passive_zoom; double items_active_zoom; double items_passive_zoom; double categories_active_alpha; double categories_passive_alpha; double items_active_alpha; double items_passive_alpha; double shadow_offset; double font2_size; double thumbnail_width; double left_thumbnail_width; double savestate_thumbnail_width; double cursor_size; double icon_spacing_horizontal; double icon_spacing_vertical; int margins_screen_top; double margins_screen_left; int margins_title_left; int margins_title_top; int margins_title_bottom; double margins_label_left; unsigned int margins_label_top; double margins_setting_left; int margins_dialog; int margins_slice; double icon_size; unsigned int font_size; } ;
typedef  TYPE_2__ xmb_handle_t ;
struct TYPE_6__ {float menu_scale_factor; } ;
struct TYPE_8__ {TYPE_1__ floats; } ;
typedef  TYPE_3__ settings_t ;

/* Variables and functions */
 TYPE_3__* config_get_ptr () ; 
 int /*<<< orphan*/  menu_display_set_header_height (unsigned int) ; 
 double* scale_mod ; 

__attribute__((used)) static void xmb_layout_ps3(xmb_handle_t *xmb, int width)
{
   unsigned new_font_size, new_header_height;
   settings_t *settings          = config_get_ptr();

   float scale_factor            =
      (settings->floats.menu_scale_factor * (float)width) / 1920.0f;

   xmb->above_subitem_offset     =   1.5;
   xmb->above_item_offset        =  -1.0;
   xmb->active_item_factor       =   3.0;
   xmb->under_item_offset        =   5.0;

   xmb->categories_active_zoom   = 1.0;
   xmb->categories_passive_zoom  = 0.5;
   xmb->items_active_zoom        = 1.0;
   xmb->items_passive_zoom       = 0.5;

   xmb->categories_active_alpha  = 1.0;
   xmb->categories_passive_alpha = 0.85;
   xmb->items_active_alpha       = 1.0;
   xmb->items_passive_alpha      = 0.85;

   xmb->shadow_offset            = 2.0;

   new_font_size                 = 32.0  * scale_factor;
   xmb->font2_size               = 24.0  * scale_factor;
   new_header_height             = 128.0 * scale_factor;

   xmb->thumbnail_width          = 1024.0 * scale_factor;
   xmb->left_thumbnail_width     = 1024.0 * scale_factor;
   xmb->savestate_thumbnail_width= 460.0 * scale_factor;
   xmb->cursor_size              = 64.0 * scale_factor;

   xmb->icon_spacing_horizontal  = 200.0 * scale_factor;
   xmb->icon_spacing_vertical    = 64.0 * scale_factor;

   xmb->margins_screen_top       = (256+32) * scale_factor;
   xmb->margins_screen_left      = 336.0 * scale_factor;

   xmb->margins_title_left       = 60 * scale_factor;
   xmb->margins_title_top        = 60 * scale_factor + new_font_size / 3;
   xmb->margins_title_bottom     = 60 * scale_factor - new_font_size / 3;

   xmb->margins_label_left       = 85.0 * scale_factor;
   xmb->margins_label_top        = new_font_size / 3.0;

   xmb->margins_setting_left     = 600.0 * scale_factor * scale_mod[6];
   xmb->margins_dialog           = 48 * scale_factor;

   xmb->margins_slice            = 16;

   xmb->icon_size                = 128.0 * scale_factor;
   xmb->font_size                = new_font_size;

   menu_display_set_header_height(new_header_height);
}