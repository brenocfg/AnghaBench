#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct string_list {size_t size; } ;
struct TYPE_3__ {char* src_str; int field_width; int field_height; char* dst_str; float* y_offset; char* top_fade_str; char* bottom_fade_str; float* top_fade_y_offset; float* bottom_fade_y_offset; float* top_fade_alpha; float* bottom_fade_alpha; int type_enum; int /*<<< orphan*/  bottom_fade_str_len; int /*<<< orphan*/  top_fade_str_len; scalar_t__ fade_enabled; int /*<<< orphan*/  dst_str_len; int /*<<< orphan*/  idx; int /*<<< orphan*/  font_scale; int /*<<< orphan*/  font; } ;
typedef  TYPE_1__ menu_animation_ctx_line_ticker_smooth_t ;

/* Variables and functions */
#define  TICKER_TYPE_BOUNCE 129 
#define  TICKER_TYPE_LOOP 128 
 int /*<<< orphan*/  build_line_ticker_string (int,size_t,struct string_list*,char*,int /*<<< orphan*/ ) ; 
 int font_driver_get_line_height (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int font_driver_get_message_width (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  menu_animation_line_ticker_smooth_generic (int /*<<< orphan*/ ,scalar_t__,size_t,size_t,size_t,size_t,size_t*,size_t*,float*,int*,size_t*,float*,float*,size_t*,float*,float*) ; 
 int /*<<< orphan*/  menu_animation_line_ticker_smooth_loop (int /*<<< orphan*/ ,scalar_t__,size_t,size_t,size_t,size_t,size_t*,size_t*,float*,int*,size_t*,float*,float*,size_t*,float*,float*) ; 
 scalar_t__ string_is_empty (char*) ; 
 int /*<<< orphan*/  string_list_free (struct string_list*) ; 
 struct string_list* string_split (char*,char*) ; 
 int /*<<< orphan*/  strlcpy (char*,char*,int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 int ticker_is_active ; 
 int /*<<< orphan*/  word_wrap (char*,char*,int,int,int /*<<< orphan*/ ) ; 

bool menu_animation_line_ticker_smooth(menu_animation_ctx_line_ticker_smooth_t *line_ticker)
{
   char *wrapped_str              = NULL;
   struct string_list *lines      = NULL;
   int glyph_width                = 0;
   int glyph_height               = 0;
   size_t line_len                = 0;
   size_t max_display_lines       = 0;
   size_t num_display_lines       = 0;
   size_t line_offset             = 0;
   size_t top_fade_line_offset    = 0;
   size_t bottom_fade_line_offset = 0;
   bool fade_active               = false;
   bool success                   = false;
   bool is_active                 = false;

   /* Sanity check */
   if (!line_ticker)
      return false;

   if (!line_ticker->font ||
       string_is_empty(line_ticker->src_str) ||
       (line_ticker->field_width < 1) ||
       (line_ticker->field_height < 1))
      goto end;

   /* Get font dimensions */

   /* > Width
    *   This is a bit of a fudge. Performing a 'font aware'
    *   (i.e. character display width) word wrap is too CPU
    *   intensive, so we just sample the width of a common
    *   character and hope for the best. (We choose 'a' because
    *   this is what Ozone uses for spacing calculations, and
    *   it is proven to work quite well) */
   glyph_width = font_driver_get_message_width(
         line_ticker->font, "a", 1, line_ticker->font_scale);

   if (glyph_width < 0)
      goto end;

   /* > Height */
   glyph_height = font_driver_get_line_height(
         line_ticker->font, line_ticker->font_scale);

   if (glyph_height < 0)
      goto end;

   /* Determine line wrap parameters */
   line_len          = (size_t)(line_ticker->field_width  / glyph_width);
   max_display_lines = (size_t)(line_ticker->field_height / glyph_height);

   if ((line_len < 1) || (max_display_lines < 1))
      goto end;

   /* Line wrap input string */
   wrapped_str = (char*)malloc((strlen(line_ticker->src_str) + 1) * sizeof(char));
   if (!wrapped_str)
      goto end;

   word_wrap(
         wrapped_str,
         line_ticker->src_str,
         (int)line_len,
         true, 0);

   if (string_is_empty(wrapped_str))
      goto end;

   /* Split into component lines */
   lines = string_split(wrapped_str, "\n");
   if (!lines)
      goto end;

   /* Check whether total number of lines fits within
    * the set field limit */
   if (lines->size <= max_display_lines)
   {
      strlcpy(line_ticker->dst_str, wrapped_str, line_ticker->dst_str_len);
      *line_ticker->y_offset = 0.0f;

      /* No fade animation is required */
      if (line_ticker->fade_enabled)
      {
         if (line_ticker->top_fade_str_len > 0)
            line_ticker->top_fade_str[0] = '\0';

         if (line_ticker->bottom_fade_str_len > 0)
            line_ticker->bottom_fade_str[0] = '\0';

         *line_ticker->top_fade_y_offset = 0.0f;
         *line_ticker->bottom_fade_y_offset = 0.0f;

         *line_ticker->top_fade_alpha = 0.0f;
         *line_ticker->bottom_fade_alpha = 0.0f;
      }

      success = true;
      goto end;
   }

   /* Determine which lines should be shown, along with
    * y axis draw offset */
   switch (line_ticker->type_enum)
   {
      case TICKER_TYPE_LOOP:
      {
         menu_animation_line_ticker_smooth_loop(
               line_ticker->idx,
               line_ticker->fade_enabled,
               line_len, (size_t)glyph_height,
               max_display_lines, lines->size,
               &num_display_lines, &line_offset, line_ticker->y_offset,
               &fade_active,
               &top_fade_line_offset, line_ticker->top_fade_y_offset, line_ticker->top_fade_alpha,
               &bottom_fade_line_offset, line_ticker->bottom_fade_y_offset, line_ticker->bottom_fade_alpha);

         break;
      }
      case TICKER_TYPE_BOUNCE:
      default:
      {
         menu_animation_line_ticker_smooth_generic(
               line_ticker->idx,
               line_ticker->fade_enabled,
               line_len, (size_t)glyph_height,
               max_display_lines, lines->size,
               &num_display_lines, &line_offset, line_ticker->y_offset,
               &fade_active,
               &top_fade_line_offset, line_ticker->top_fade_y_offset, line_ticker->top_fade_alpha,
               &bottom_fade_line_offset, line_ticker->bottom_fade_y_offset, line_ticker->bottom_fade_alpha);

         break;
      }
   }

   /* Build output string from required lines */
   build_line_ticker_string(
         num_display_lines, line_offset, lines,
         line_ticker->dst_str, line_ticker->dst_str_len);

   /* Extract top/bottom fade strings, if required */
   if (fade_active)
   {
      /* We waste a handful of clock cycles by using
       * build_line_ticker_string() here, but it saves
       * rewriting a heap of code... */
      build_line_ticker_string(
            1, top_fade_line_offset, lines,
            line_ticker->top_fade_str, line_ticker->top_fade_str_len);

      build_line_ticker_string(
            1, bottom_fade_line_offset, lines,
            line_ticker->bottom_fade_str, line_ticker->bottom_fade_str_len);
   }

   success          = true;
   is_active        = true;
   ticker_is_active = true;

end:

   if (wrapped_str)
   {
      free(wrapped_str);
      wrapped_str = NULL;
   }

   if (lines)
   {
      string_list_free(lines);
      lines = NULL;
   }

   if (!success)
   {
      if (line_ticker->dst_str_len > 0)
         line_ticker->dst_str[0] = '\0';

      if (line_ticker->fade_enabled)
      {
         if (line_ticker->top_fade_str_len > 0)
            line_ticker->top_fade_str[0] = '\0';

         if (line_ticker->bottom_fade_str_len > 0)
            line_ticker->bottom_fade_str[0] = '\0';

         *line_ticker->top_fade_alpha = 0.0f;
         *line_ticker->bottom_fade_alpha = 0.0f;
      }
   }

   return is_active;
}