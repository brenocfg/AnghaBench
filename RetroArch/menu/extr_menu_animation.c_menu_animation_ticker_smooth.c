#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* src_str; int dst_str_len; int field_width; int glyph_width; char* dst_str; unsigned int* dst_str_width; char* spacer; int type_enum; scalar_t__* x_offset; int /*<<< orphan*/  idx; int /*<<< orphan*/  font_scale; int /*<<< orphan*/  font; int /*<<< orphan*/  selected; } ;
typedef  TYPE_1__ menu_animation_ctx_ticker_smooth_t ;

/* Variables and functions */
#define  TICKER_TYPE_BOUNCE 129 
#define  TICKER_TYPE_LOOP 128 
 int /*<<< orphan*/  build_ticker_loop_string (char*,char*,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,char*,int) ; 
 scalar_t__ calloc (size_t,int) ; 
 int font_driver_get_message_width (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (unsigned int*) ; 
 int menu_animation_ticker_smooth_fw (TYPE_1__*) ; 
 int /*<<< orphan*/  menu_animation_ticker_smooth_generic (int /*<<< orphan*/ ,unsigned int*,size_t,unsigned int,int,unsigned int*,unsigned int*,scalar_t__*,unsigned int*) ; 
 int /*<<< orphan*/  menu_animation_ticker_smooth_loop (int /*<<< orphan*/ ,unsigned int*,size_t,unsigned int*,size_t,unsigned int,unsigned int,int,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,scalar_t__*,unsigned int*) ; 
 scalar_t__ string_is_empty (char*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,int) ; 
 int ticker_is_active ; 
 char* ticker_spacer_default ; 
 int /*<<< orphan*/  utf8cpy (char*,int,char*,unsigned int) ; 
 size_t utf8len (char*) ; 
 char* utf8skip (char const*,unsigned int) ; 

bool menu_animation_ticker_smooth(menu_animation_ctx_ticker_smooth_t *ticker)
{
   size_t i;
   size_t src_str_len           = 0;
   size_t spacer_len            = 0;
   unsigned src_str_width       = 0;
   unsigned spacer_width        = 0;
   unsigned *src_char_widths    = NULL;
   unsigned *spacer_char_widths = NULL;
   const char *str_ptr          = NULL;
   bool success                 = false;
   bool is_active               = false;

   /* Sanity check */
   if (string_is_empty(ticker->src_str) ||
       (ticker->dst_str_len < 1) ||
       (ticker->field_width < 1) ||
       (!ticker->font && (ticker->glyph_width < 1)))
      goto end;

   /* If we are using a fixed width font (ticker->font == NULL),
    * switch to optimised code path */
   if (!ticker->font)
      return menu_animation_ticker_smooth_fw(ticker);

   /* Find the display width of each character in
    * the src string + total width */
   src_str_len = utf8len(ticker->src_str);
   if (src_str_len < 1)
      goto end;

   src_char_widths = (unsigned*)calloc(src_str_len, sizeof(unsigned));
   if (!src_char_widths)
      goto end;

   str_ptr = ticker->src_str;
   for (i = 0; i < src_str_len; i++)
   {
      int glyph_width = font_driver_get_message_width(
            ticker->font, str_ptr, 1, ticker->font_scale);

      if (glyph_width < 0)
         goto end;

      src_char_widths[i] = (unsigned)glyph_width;
      src_str_width += (unsigned)glyph_width;

      str_ptr = utf8skip(str_ptr, 1);
   }

   /* If total src string width is <= text field width, we
    * can just copy the entire string */
   if (src_str_width <= ticker->field_width)
   {
      utf8cpy(ticker->dst_str, ticker->dst_str_len, ticker->src_str, src_str_len);

      if (ticker->dst_str_width)
         *ticker->dst_str_width = src_str_width;
      *ticker->x_offset = 0;
      success = true;
      goto end;
   }

   /* If entry is not selected, just clip input string
    * and add '...' suffix */
   if (!ticker->selected)
   {
      unsigned text_width;
      unsigned current_width = 0;
      unsigned num_chars     = 0;
      int period_width       =
            font_driver_get_message_width(ticker->font, ".", 1, ticker->font_scale);

      /* Sanity check */
      if (period_width < 0)
         goto end;

      if (ticker->field_width < (3 * period_width))
         goto end;

      /* Determine number of characters to copy */
      text_width = ticker->field_width - (3 * period_width);
      while (true)
      {
         current_width += src_char_widths[num_chars];

         if (current_width > text_width)
         {
            /* Have to go back one in order to get 'actual'
             * value for dst_str_width */
            current_width -= src_char_widths[num_chars];
            break;
         }

         num_chars++;
      }

      /* Copy string segment + add suffix */
      utf8cpy(ticker->dst_str, ticker->dst_str_len, ticker->src_str, num_chars);
      strlcat(ticker->dst_str, "...", ticker->dst_str_len);

      if (ticker->dst_str_width)
         *ticker->dst_str_width = current_width + (3 * period_width);
      *ticker->x_offset = 0;
      success = true;
      goto end;
   }

   /* If we get this far, then a scrolling animation
    * is required... */

   /* Use default spacer, if none is provided */
   if (!ticker->spacer)
      ticker->spacer = ticker_spacer_default;

   /* Find the display width of each character in
    * the spacer */
   spacer_len = utf8len(ticker->spacer);
   if (spacer_len < 1)
      goto end;

   spacer_char_widths = (unsigned*)calloc(spacer_len,  sizeof(unsigned));
   if (!spacer_char_widths)
      goto end;

   str_ptr = ticker->spacer;
   for (i = 0; i < spacer_len; i++)
   {
      int glyph_width = font_driver_get_message_width(
            ticker->font, str_ptr, 1, ticker->font_scale);

      if (glyph_width < 0)
         goto end;

      spacer_char_widths[i] = (unsigned)glyph_width;
      spacer_width += (unsigned)glyph_width;

      str_ptr = utf8skip(str_ptr, 1);
   }

   /* Determine animation type */
   switch (ticker->type_enum)
   {
      case TICKER_TYPE_LOOP:
      {
         unsigned char_offset1 = 0;
         unsigned num_chars1   = 0;
         unsigned char_offset2 = 0;
         unsigned num_chars2   = 0;
         unsigned char_offset3 = 0;
         unsigned num_chars3   = 0;

         menu_animation_ticker_smooth_loop(
               ticker->idx,
               src_char_widths, src_str_len,
               spacer_char_widths, spacer_len,
               src_str_width, spacer_width, ticker->field_width,
               &char_offset1, &num_chars1,
               &char_offset2, &num_chars2,
               &char_offset3, &num_chars3,
               ticker->x_offset, ticker->dst_str_width);

         build_ticker_loop_string(
               ticker->src_str, ticker->spacer,
               char_offset1, num_chars1,
               char_offset2, num_chars2,
               char_offset3, num_chars3,
               ticker->dst_str, ticker->dst_str_len);

         break;
      }
      case TICKER_TYPE_BOUNCE:
      default:
      {
         unsigned char_offset = 0;
         unsigned num_chars   = 0;

         ticker->dst_str[0] = '\0';

         menu_animation_ticker_smooth_generic(
               ticker->idx,
               src_char_widths, src_str_len, src_str_width, ticker->field_width,
               &char_offset, &num_chars, ticker->x_offset, ticker->dst_str_width);

         /* Copy required substring */
         if (num_chars > 0)
         {
            utf8cpy(
                  ticker->dst_str, ticker->dst_str_len,
                  utf8skip(ticker->src_str, char_offset), num_chars);
         }

         break;
      }
   }

   success          = true;
   is_active        = true;
   ticker_is_active = true;

end:

   if (src_char_widths)
   {
      free(src_char_widths);
      src_char_widths = NULL;
   }

   if (spacer_char_widths)
   {
      free(spacer_char_widths);
      spacer_char_widths = NULL;
   }

   if (!success)
   {
      *ticker->x_offset = 0;

      if (ticker->dst_str_len > 0)
         ticker->dst_str[0] = '\0';
   }

   return is_active;
}