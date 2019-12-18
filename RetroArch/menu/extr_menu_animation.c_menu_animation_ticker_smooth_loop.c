#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  unsigned int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ticker_smooth_scan_characters (unsigned int const*,size_t,unsigned int,unsigned int,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void menu_animation_ticker_smooth_loop(uint64_t idx,
      const unsigned *char_widths, size_t num_chars,
      const unsigned *spacer_widths, size_t num_spacer_chars,
      unsigned str_width, unsigned spacer_width, unsigned field_width,
      unsigned *char_offset1, unsigned *num_chars_to_copy1,
      unsigned *char_offset2, unsigned *num_chars_to_copy2,
      unsigned *char_offset3, unsigned *num_chars_to_copy3,
      unsigned *x_offset, unsigned *dst_str_width)

{
   unsigned ticker_period   = str_width + spacer_width;
   unsigned phase           = idx % ticker_period;

   unsigned remaining_width = field_width;

   /* Initialise output variables to 'sane' values */
   *char_offset1       = 0;
   *num_chars_to_copy1 = 0;
   *char_offset2       = 0;
   *num_chars_to_copy2 = 0;
   *char_offset3       = 0;
   *num_chars_to_copy3 = 0;
   *x_offset           = 0;
   if (dst_str_width)
      *dst_str_width   = 0;

   /* Sanity check */
   if ((num_chars < 1) || (num_spacer_chars < 1))
      return;

   /* Looping text is composed of up to three strings,
    * where string 1 and 2 are different regions of the
    * source text and string 2 is a spacer:
    * 
    *     |----field_width----|
    * [string 1][string 2][string 3]
    */

   /* String 1 */
   if (phase < str_width)
   {
      unsigned scroll_offset = phase;
      unsigned display_width = 0;
      unsigned str1_width    = 0;

      ticker_smooth_scan_characters(
            char_widths, num_chars, remaining_width, scroll_offset,
            char_offset1, num_chars_to_copy1, x_offset, &str1_width, &display_width);

      /* Update remaining width */
      remaining_width -= display_width;

      /* Update dst_str_width */
      if (dst_str_width)
         *dst_str_width += str1_width;
   }

   /* String 2 */
   if (remaining_width > 0)
   {
      unsigned scroll_offset = 0;
      unsigned display_width = 0;
      unsigned str2_width    = 0;
      unsigned x_offset2     = 0;

      /* Check whether we've passed the end of string 1 */
      if (phase > str_width)
         scroll_offset = phase - str_width;
      else
         scroll_offset = 0;

      ticker_smooth_scan_characters(
            spacer_widths, num_spacer_chars, remaining_width, scroll_offset,
            char_offset2, num_chars_to_copy2, &x_offset2, &str2_width, &display_width);

      /* > Update remaining width */
      remaining_width -= display_width;

      /* Update dst_str_width */
      if (dst_str_width)
         *dst_str_width += str2_width;

      /* If scroll_offset is greater than zero, it means
       * string 2 is the first string to be displayed
       * > ticker x offset is therefore string 2's offset */
      if (scroll_offset > 0)
         *x_offset = x_offset2;
   }

   /* String 3 */
   if (remaining_width > 0)
   {
      /* String 3 is only shown when string 2 is shown,
       * so we can take some shortcuts... */
      unsigned i;
      unsigned text_width = 0;
      *char_offset3       = 0;

      /* Determine number of characters to copy */
      for (i = 0; i < num_chars; i++)
      {
         text_width += char_widths[i];

         if (text_width <= remaining_width)
            (*num_chars_to_copy3)++;
         else
         {
            /* Update dst_str_width */
            if (dst_str_width)
               *dst_str_width += text_width - char_widths[i];
            break;
         }
      }
   }
}