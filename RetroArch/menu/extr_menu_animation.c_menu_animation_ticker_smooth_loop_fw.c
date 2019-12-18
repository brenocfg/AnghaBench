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
 int /*<<< orphan*/  ticker_smooth_scan_string_fw (size_t,unsigned int,unsigned int,unsigned int,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void menu_animation_ticker_smooth_loop_fw(uint64_t idx,
      unsigned str_width, size_t num_chars,
      unsigned spacer_width, size_t num_spacer_chars,
      unsigned glyph_width, unsigned field_width,
      unsigned *char_offset1, unsigned *num_chars_to_copy1,
      unsigned *char_offset2, unsigned *num_chars_to_copy2,
      unsigned *char_offset3, unsigned *num_chars_to_copy3,
      unsigned *x_offset)
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

      ticker_smooth_scan_string_fw(
            num_chars, glyph_width, remaining_width, scroll_offset,
            char_offset1, num_chars_to_copy1, x_offset);

      /* Update remaining width
       * Note: We can avoid all the display_width shenanigans
       * here (c.f. menu_animation_ticker_smooth_loop()) because
       * the font width is constant - i.e. we don't have to wrangle
       * out the width of the last 'non-copied' character since it
       * is known a priori, so we can just subtract the string width
       * + offset here, and perform an 'if (remaining_width > glyph_width)'
       * for strings 2 and 3 */
      remaining_width -= (*x_offset + (*num_chars_to_copy1 * glyph_width));
   }

   /* String 2 */
   if (remaining_width > glyph_width)
   {
      unsigned scroll_offset = 0;
      unsigned x_offset2     = 0;

      /* Check whether we've passed the end of string 1 */
      if (phase > str_width)
         scroll_offset = phase - str_width;
      else
         scroll_offset = 0;

      ticker_smooth_scan_string_fw(
            num_spacer_chars, glyph_width, remaining_width, scroll_offset,
            char_offset2, num_chars_to_copy2, &x_offset2);

      /* > Update remaining width */
      remaining_width -= (x_offset2 + (*num_chars_to_copy2 * glyph_width));

      /* If scroll_offset is greater than zero, it means
       * string 2 is the first string to be displayed
       * > ticker x offset is therefore string 2's offset */
      if (scroll_offset > 0)
         *x_offset = x_offset2;
   }

   /* String 3 */
   if (remaining_width > glyph_width)
   {
      /* String 3 is only shown when string 2 is shown,
       * so we can take some shortcuts... */
      *char_offset3       = 0;

      /* Determine number of characters to copy */
      *num_chars_to_copy3 = remaining_width / glyph_width;
      *num_chars_to_copy3 = (*num_chars_to_copy3 > num_chars) ? num_chars : *num_chars_to_copy3;
   }
}