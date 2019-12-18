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
struct TYPE_3__ {unsigned int glyph_width; unsigned int field_width; char* dst_str; scalar_t__ dst_str_len; unsigned int* dst_str_width; int type_enum; scalar_t__* x_offset; scalar_t__ src_str; int /*<<< orphan*/  idx; scalar_t__ spacer; int /*<<< orphan*/  selected; } ;
typedef  TYPE_1__ menu_animation_ctx_ticker_smooth_t ;

/* Variables and functions */
#define  TICKER_TYPE_BOUNCE 129 
#define  TICKER_TYPE_LOOP 128 
 int /*<<< orphan*/  build_ticker_loop_string (scalar_t__,scalar_t__,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,unsigned int,char*,scalar_t__) ; 
 int /*<<< orphan*/  menu_animation_ticker_smooth_generic_fw (int /*<<< orphan*/ ,unsigned int,size_t,unsigned int,unsigned int,unsigned int*,unsigned int*,scalar_t__*) ; 
 int /*<<< orphan*/  menu_animation_ticker_smooth_loop_fw (int /*<<< orphan*/ ,unsigned int,size_t,unsigned int,size_t,unsigned int,unsigned int,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,scalar_t__*) ; 
 int /*<<< orphan*/  strlcat (char*,char*,scalar_t__) ; 
 int ticker_is_active ; 
 scalar_t__ ticker_spacer_default ; 
 int /*<<< orphan*/  utf8cpy (char*,scalar_t__,scalar_t__,unsigned int) ; 
 size_t utf8len (scalar_t__) ; 
 scalar_t__ utf8skip (scalar_t__,unsigned int) ; 

bool menu_animation_ticker_smooth_fw(menu_animation_ctx_ticker_smooth_t *ticker)
{
   size_t src_str_len           = 0;
   size_t spacer_len            = 0;
   unsigned glyph_width         = ticker->glyph_width;
   unsigned src_str_width       = 0;
   unsigned spacer_width        = 0;
   bool success                 = false;
   bool is_active               = false;

   /* Sanity check has already been performed by
    * menu_animation_ticker_smooth() - no need to
    * repeat */

   /* Get length + width of src string */
   src_str_len = utf8len(ticker->src_str);
   if (src_str_len < 1)
      goto end;

   src_str_width = src_str_len * glyph_width;

   /* If src string width is <= text field width, we
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
      unsigned num_chars    = 0;
      unsigned suffix_len   = 3;
      unsigned suffix_width = suffix_len * glyph_width;

      /* Sanity check */
      if (ticker->field_width < suffix_width)
         goto end;

      /* Determine number of characters to copy */
      num_chars = (ticker->field_width - suffix_width) / glyph_width;

      /* Copy string segment + add suffix */
      utf8cpy(ticker->dst_str, ticker->dst_str_len, ticker->src_str, num_chars);
      strlcat(ticker->dst_str, "...", ticker->dst_str_len);

      if (ticker->dst_str_width)
         *ticker->dst_str_width = (num_chars * glyph_width) + suffix_width;
      *ticker->x_offset = 0;
      success = true;
      goto end;
   }

   /* If we get this far, then a scrolling animation
    * is required... */

   /* Use default spacer, if none is provided */
   if (!ticker->spacer)
      ticker->spacer = ticker_spacer_default;

   /* Get length + width of spacer */
   spacer_len = utf8len(ticker->spacer);
   if (spacer_len < 1)
      goto end;

   spacer_width = spacer_len * glyph_width;

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

         menu_animation_ticker_smooth_loop_fw(
               ticker->idx,
               src_str_width, src_str_len, spacer_width, spacer_len,
               glyph_width, ticker->field_width,
               &char_offset1, &num_chars1,
               &char_offset2, &num_chars2,
               &char_offset3, &num_chars3,
               ticker->x_offset);

         build_ticker_loop_string(
               ticker->src_str, ticker->spacer,
               char_offset1, num_chars1,
               char_offset2, num_chars2,
               char_offset3, num_chars3,
               ticker->dst_str, ticker->dst_str_len);

         if (ticker->dst_str_width)
            *ticker->dst_str_width = (num_chars1 + num_chars2 + num_chars3) * glyph_width;

         break;
      }
      case TICKER_TYPE_BOUNCE:
      default:
      {
         unsigned char_offset = 0;
         unsigned num_chars   = 0;

         ticker->dst_str[0] = '\0';

         menu_animation_ticker_smooth_generic_fw(
               ticker->idx,
               src_str_width, src_str_len, glyph_width, ticker->field_width,
               &char_offset, &num_chars, ticker->x_offset);

         /* Copy required substring */
         if (num_chars > 0)
         {
            utf8cpy(
                  ticker->dst_str, ticker->dst_str_len,
                  utf8skip(ticker->src_str, char_offset), num_chars);
         }

         if (ticker->dst_str_width)
            *ticker->dst_str_width = num_chars * glyph_width;

         break;
      }
   }

   success          = true;
   is_active        = true;
   ticker_is_active = true;

end:

   if (!success)
   {
      *ticker->x_offset = 0;

      if (ticker->dst_str_len > 0)
         ticker->dst_str[0] = '\0';
   }

   return is_active;
}