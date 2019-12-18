#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_12__ {int /*<<< orphan*/  hover_color; int /*<<< orphan*/  shadow_color; int /*<<< orphan*/  normal_color; int /*<<< orphan*/  border_light_color; int /*<<< orphan*/  border_dark_color; int /*<<< orphan*/  bg_light_color; int /*<<< orphan*/  bg_dark_color; } ;
struct TYPE_13__ {int bg_thickness; int border_thickness; TYPE_1__ colors; scalar_t__ shadow_enable; scalar_t__ border_enable; } ;
typedef  TYPE_2__ rgui_t ;
typedef  int /*<<< orphan*/  msg ;
struct TYPE_14__ {char* s; unsigned int len; char const* str; int selected; } ;
typedef  TYPE_3__ menu_animation_ctx_ticker_t ;
struct TYPE_15__ {int selected; unsigned int field_width; char const* src_str; char* dst_str; int dst_str_len; unsigned int* x_offset; } ;
typedef  TYPE_4__ menu_animation_ctx_ticker_smooth_t ;
typedef  int /*<<< orphan*/  input_label_buf ;
struct TYPE_16__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 unsigned int FONT_HEIGHT ; 
 int FONT_HEIGHT_STRIDE ; 
 unsigned int FONT_WIDTH ; 
 unsigned int FONT_WIDTH_STRIDE ; 
 unsigned int OSK_CHARS_PER_LINE ; 
 int /*<<< orphan*/  RGUI_SYMBOL_BACKSPACE ; 
 int /*<<< orphan*/  RGUI_SYMBOL_ENTER ; 
 int /*<<< orphan*/  RGUI_SYMBOL_NEXT ; 
 int /*<<< orphan*/  RGUI_SYMBOL_SHIFT_DOWN ; 
 int /*<<< orphan*/  RGUI_SYMBOL_SHIFT_UP ; 
 int /*<<< orphan*/  RGUI_SYMBOL_TEXT_CURSOR ; 
 int /*<<< orphan*/  blit_line (unsigned int,int,int,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blit_symbol (unsigned int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  menu_animation_ticker (TYPE_3__*) ; 
 int /*<<< orphan*/  menu_animation_ticker_smooth (TYPE_4__*) ; 
 int /*<<< orphan*/  menu_display_get_fb_size (unsigned int*,unsigned int*,size_t*) ; 
 char** menu_event_get_osk_grid () ; 
 int menu_event_get_osk_ptr () ; 
 char* menu_input_dialog_get_buffer () ; 
 char* menu_input_dialog_get_label_buffer () ; 
 int /*<<< orphan*/  rgui_color_rect (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rgui_fill_rect (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_9__ rgui_frame_buf ; 
 int /*<<< orphan*/  rgui_render_messagebox (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  string_is_empty (char const*) ; 
 scalar_t__ string_is_equal (char const*,char*) ; 
 scalar_t__ strlen (char const*) ; 
 unsigned int utf8len (char*) ; 

__attribute__((used)) static void rgui_render_osk(
      rgui_t *rgui,
      menu_animation_ctx_ticker_t *ticker, menu_animation_ctx_ticker_smooth_t *ticker_smooth,
      bool use_smooth_ticker)
{
   size_t fb_pitch;
   unsigned fb_width, fb_height;
   size_t key_index;
   
   unsigned input_label_max_length;
   unsigned input_str_max_length;
   unsigned input_offset_x, input_offset_y;
   
   unsigned key_width, key_height;
   unsigned key_text_offset_x, key_text_offset_y;
   unsigned ptr_width, ptr_height;
   unsigned ptr_offset_x, ptr_offset_y;
   
   unsigned keyboard_width, keyboard_height;
   unsigned keyboard_offset_x, keyboard_offset_y;
   
   unsigned osk_width, osk_height;
   unsigned osk_x, osk_y;
   
   int osk_ptr             = menu_event_get_osk_ptr();
   char **osk_grid         = menu_event_get_osk_grid();
   const char *input_str   = menu_input_dialog_get_buffer();
   const char *input_label = menu_input_dialog_get_label_buffer();
   
   /* Sanity check 1 */
   if (!rgui_frame_buf.data || osk_ptr < 0 || osk_ptr >= 44 || !osk_grid[0])
      return;
   
   /* Get dimensions/layout */
   menu_display_get_fb_size(&fb_width, &fb_height, &fb_pitch);
   
   key_text_offset_x      = 8;
   key_text_offset_y      = 6;
   key_width              = FONT_WIDTH  + (key_text_offset_x * 2);
   key_height             = FONT_HEIGHT + (key_text_offset_y * 2);
   ptr_offset_x           = 2;
   ptr_offset_y           = 2;
   ptr_width              = key_width  - (ptr_offset_x * 2);
   ptr_height             = key_height - (ptr_offset_y * 2);
   keyboard_width         = key_width  * OSK_CHARS_PER_LINE;
   keyboard_height        = key_height * 4;
   keyboard_offset_x      = 10;
   keyboard_offset_y      = 10 + 15 + (2 * FONT_HEIGHT_STRIDE);
   input_label_max_length = (keyboard_width / FONT_WIDTH_STRIDE);
   input_str_max_length   = input_label_max_length - 1;
   input_offset_x         = 10 + (keyboard_width - (input_label_max_length * FONT_WIDTH_STRIDE)) / 2;
   input_offset_y         = 10;
   osk_width              = keyboard_width + 20;
   osk_height             = keyboard_offset_y + keyboard_height + 10;
   osk_x                  = (fb_width - osk_width) / 2;
   osk_y                  = (fb_height - osk_height) / 2;
   
   /* Sanity check 2 */
   if ((osk_width + 2 > fb_width) || (osk_height + 2 > fb_height))
   {
      /* This can never happen, but have to make sure...
       * If OSK cannot physically fit on the screen,
       * fallback to old style 'message box' implementation */
      char msg[255];
      msg[0] = '\0';
      
      snprintf(msg, sizeof(msg), "%s\n%s", input_label, input_str);
      rgui_render_messagebox(rgui, msg);
      
      return;
   }
   
   /* Draw background */
   rgui_fill_rect(rgui_frame_buf.data, fb_width, fb_height,
         osk_x + 5, osk_y + 5, osk_width - 10, osk_height - 10,
         rgui->colors.bg_dark_color, rgui->colors.bg_light_color, rgui->bg_thickness);
   
   /* Draw border */
   if (rgui->border_enable)
   {
      uint16_t border_dark_color  = rgui->colors.border_dark_color;
      uint16_t border_light_color = rgui->colors.border_light_color;
      bool border_thickness       = rgui->border_thickness;
      
      /* Draw drop shadow, if required */
      if (rgui->shadow_enable)
      {
         uint16_t shadow_color = rgui->colors.shadow_color;
         
         /* Frame */
         rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
               osk_x + 5, osk_y + 5, osk_width - 10, 1, shadow_color);
         rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
               osk_x + osk_width, osk_y + 1, 1, osk_height, shadow_color);
         rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
               osk_x + 1, osk_y + osk_height, osk_width, 1, shadow_color);
         rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
               osk_x + 5, osk_y + 5, 1, osk_height - 10, shadow_color);
         /* Divider */
         rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
               osk_x + 5, osk_y + keyboard_offset_y - 5, osk_width - 10, 1, shadow_color);
      }
      
      /* Frame */
      rgui_fill_rect(rgui_frame_buf.data, fb_width, fb_height,
            osk_x, osk_y, osk_width - 5, 5,
            border_dark_color, border_light_color, border_thickness);
      rgui_fill_rect(rgui_frame_buf.data, fb_width, fb_height,
            osk_x + osk_width - 5, osk_y, 5, osk_height - 5,
            border_dark_color, border_light_color, border_thickness);
      rgui_fill_rect(rgui_frame_buf.data, fb_width, fb_height,
            osk_x + 5, osk_y + osk_height - 5, osk_width - 5, 5,
            border_dark_color, border_light_color, border_thickness);
      rgui_fill_rect(rgui_frame_buf.data, fb_width, fb_height,
            osk_x, osk_y + 5, 5, osk_height - 5,
            border_dark_color, border_light_color, border_thickness);
      /* Divider */
      rgui_fill_rect(rgui_frame_buf.data, fb_width, fb_height,
            osk_x + 5, osk_y + keyboard_offset_y - 10, osk_width - 10, 5,
            border_dark_color, border_light_color, border_thickness);
   }
   
   /* Draw input label text */
   if (!string_is_empty(input_label))
   {
      char input_label_buf[255];
      unsigned input_label_length;
      int input_label_x, input_label_y;
      unsigned ticker_x_offset = 0;
      
      input_label_buf[0] = '\0';
      
      if (use_smooth_ticker)
      {
         ticker_smooth->selected    = true;
         ticker_smooth->field_width = input_label_max_length * FONT_WIDTH_STRIDE;
         ticker_smooth->src_str     = input_label;
         ticker_smooth->dst_str     = input_label_buf;
         ticker_smooth->dst_str_len = sizeof(input_label_buf);
         ticker_smooth->x_offset    = &ticker_x_offset;
         
         menu_animation_ticker_smooth(ticker_smooth);
      }
      else
      {
         ticker->s        = input_label_buf;
         ticker->len      = input_label_max_length;
         ticker->str      = input_label;
         ticker->selected = true;
         
         menu_animation_ticker(ticker);
      }

      input_label_length = (unsigned)(utf8len(input_label_buf) * FONT_WIDTH_STRIDE);
      input_label_x      = ticker_x_offset + osk_x + input_offset_x + ((input_label_max_length * FONT_WIDTH_STRIDE) - input_label_length) / 2;
      input_label_y      = osk_y + input_offset_y;
      
      blit_line(fb_width, input_label_x, input_label_y, input_label_buf,
            rgui->colors.normal_color, rgui->colors.shadow_color);
   }
   
   /* Draw input buffer text */
   {
      unsigned input_str_char_offset;
      int input_str_x, input_str_y;
      int text_cursor_x;
      unsigned input_str_length = (unsigned)strlen(input_str);
      
      if (input_str_length > input_str_max_length)
      {
         input_str_char_offset = input_str_length - input_str_max_length;
         input_str_length      = input_str_max_length;
      }
      else
         input_str_char_offset = 0;
      
      input_str_x = osk_x + input_offset_x;
      input_str_y = osk_y + input_offset_y + FONT_HEIGHT_STRIDE;
      
      if (!string_is_empty(input_str + input_str_char_offset))
         blit_line(fb_width, input_str_x, input_str_y, input_str + input_str_char_offset,
               rgui->colors.hover_color, rgui->colors.shadow_color);
      
      /* Draw text cursor */
      text_cursor_x = osk_x + input_offset_x + (input_str_length * FONT_WIDTH_STRIDE);
      
      blit_symbol(fb_width, text_cursor_x, input_str_y, RGUI_SYMBOL_TEXT_CURSOR,
            rgui->colors.normal_color, rgui->colors.shadow_color);
   }
   
   /* Draw keyboard 'keys' */
   for (key_index = 0; key_index < 44; key_index++)
   {
      unsigned key_row     = (unsigned)(key_index / OSK_CHARS_PER_LINE);
      unsigned key_column  = (unsigned)(key_index - (key_row * OSK_CHARS_PER_LINE));
      
      int key_text_x       = osk_x + keyboard_offset_x + key_text_offset_x + (key_column * key_width);
      int key_text_y       = osk_y + keyboard_offset_y + key_text_offset_y + (key_row    * key_height);
      
      const char *key_text = osk_grid[key_index];
      
      /* 'Command' keys use custom symbols - have to
       * detect them and use blit_symbol(). Everything
       * else is plain text, and can be drawn directly
       * using blit_line(). */
#ifdef HAVE_LANGEXTRA
      if (     string_is_equal(key_text, "\xe2\x87\xa6")) /* backspace character */
         blit_symbol(fb_width, key_text_x, key_text_y, RGUI_SYMBOL_BACKSPACE,
               rgui->colors.normal_color, rgui->colors.shadow_color);
      else if (string_is_equal(key_text, "\xe2\x8f\x8e")) /* return character */
         blit_symbol(fb_width, key_text_x, key_text_y, RGUI_SYMBOL_ENTER,
               rgui->colors.normal_color, rgui->colors.shadow_color);
      else if (string_is_equal(key_text, "\xe2\x87\xa7")) /* up arrow */
         blit_symbol(fb_width, key_text_x, key_text_y, RGUI_SYMBOL_SHIFT_UP,
               rgui->colors.normal_color, rgui->colors.shadow_color);
      else if (string_is_equal(key_text, "\xe2\x87\xa9")) /* down arrow */
         blit_symbol(fb_width, key_text_x, key_text_y, RGUI_SYMBOL_SHIFT_DOWN,
               rgui->colors.normal_color, rgui->colors.shadow_color);
      else if (string_is_equal(key_text, "\xe2\x8a\x95")) /* plus sign (next button) */
         blit_symbol(fb_width, key_text_x, key_text_y, RGUI_SYMBOL_NEXT,
               rgui->colors.normal_color, rgui->colors.shadow_color);
#else
      if (     string_is_equal(key_text, "Bksp"))
         blit_symbol(fb_width, key_text_x, key_text_y, RGUI_SYMBOL_BACKSPACE,
               rgui->colors.normal_color, rgui->colors.shadow_color);
      else if (string_is_equal(key_text, "Enter"))
         blit_symbol(fb_width, key_text_x, key_text_y, RGUI_SYMBOL_ENTER,
               rgui->colors.normal_color, rgui->colors.shadow_color);
      else if (string_is_equal(key_text, "Upper"))
         blit_symbol(fb_width, key_text_x, key_text_y, RGUI_SYMBOL_SHIFT_UP,
               rgui->colors.normal_color, rgui->colors.shadow_color);
      else if (string_is_equal(key_text, "Lower"))
         blit_symbol(fb_width, key_text_x, key_text_y, RGUI_SYMBOL_SHIFT_DOWN,
               rgui->colors.normal_color, rgui->colors.shadow_color);
      else if (string_is_equal(key_text, "Next"))
         blit_symbol(fb_width, key_text_x, key_text_y, RGUI_SYMBOL_NEXT,
               rgui->colors.normal_color, rgui->colors.shadow_color);
#endif
      else
         blit_line(fb_width, key_text_x, key_text_y, key_text,
               rgui->colors.normal_color, rgui->colors.shadow_color);
      
      /* Draw selection pointer */
      if (key_index == osk_ptr)
      {
         unsigned osk_ptr_x = osk_x + keyboard_offset_x + ptr_offset_x + (key_column * key_width);
         unsigned osk_ptr_y = osk_y + keyboard_offset_y + ptr_offset_y + (key_row    * key_height);
         
         /* Draw drop shadow, if required */
         if (rgui->shadow_enable)
         {
            rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
                  osk_ptr_x + 1, osk_ptr_y + 1, 1, ptr_height, rgui->colors.shadow_color);
            rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
                  osk_ptr_x + 1, osk_ptr_y + 1, ptr_width, 1, rgui->colors.shadow_color);
            rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
                  osk_ptr_x + ptr_width, osk_ptr_y + 1, 1, ptr_height, rgui->colors.shadow_color);
            rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
                  osk_ptr_x + 1, osk_ptr_y + ptr_height, ptr_width, 1, rgui->colors.shadow_color);
         }
         
         /* Draw selection rectangle */
         rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
               osk_ptr_x, osk_ptr_y, 1, ptr_height, rgui->colors.hover_color);
         rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
               osk_ptr_x, osk_ptr_y, ptr_width, 1, rgui->colors.hover_color);
         rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
               osk_ptr_x + ptr_width - 1, osk_ptr_y, 1, ptr_height, rgui->colors.hover_color);
         rgui_color_rect(rgui_frame_buf.data, fb_width, fb_height,
               osk_ptr_x, osk_ptr_y + ptr_height - 1, ptr_width, 1, rgui->colors.hover_color);
      }
   }
}