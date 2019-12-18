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

/* Variables and functions */

__attribute__((used)) static void ticker_smooth_scan_characters(
      const unsigned *char_widths, size_t num_chars, unsigned field_width, unsigned scroll_offset,
      unsigned *char_offset, unsigned *num_chars_to_copy, unsigned *x_offset,
      unsigned *str_width, unsigned *display_width)
{
   unsigned text_width     = 0;
   unsigned scroll_pos     = scroll_offset;
   bool deferred_str_width = true;
   unsigned i;

   /* Initialise output variables to 'sane' values */
   *char_offset       = 0;
   *num_chars_to_copy = 0;
   *x_offset          = 0;
   if (str_width)
      *str_width      = 0;
   if (display_width)
      *display_width  = 0;

   /* Determine index of first character to copy */
   if (scroll_pos > 0)
   {
      for (i = 0; i < num_chars; i++)
      {
         if (scroll_pos > char_widths[i])
            scroll_pos -= char_widths[i];
         else
         {
            /* Note: It's okay for char_offset to go out
             * of range here (num_chars_to_copy will be zero
             * in this case) */
            *char_offset = i + 1;
            *x_offset = char_widths[i] - scroll_pos;
            break;
         }
      }
   }

   /* Determine number of characters to copy */
   for (i = *char_offset; i < num_chars; i++)
   {
      text_width += char_widths[i];

      if (*x_offset + text_width <= field_width)
         (*num_chars_to_copy)++;
      else
      {
         /* Get actual width of resultant string
          * (excluding x offset + end padding)
          * Note that this is only set if we exceed the
          * field width - if all characters up to the end
          * of the string are copied... */
         if (str_width)
         {
            deferred_str_width = false;
            *str_width = text_width - char_widths[i];
         }
         break;
      }
   }

   /* ...then we have to update str_width here instead */
   if (str_width)
      if (deferred_str_width)
         *str_width = text_width;

   /* Get total display width of resultant string
    * (x offset + text width + end padding) */
   if (display_width)
   {
      *display_width = *x_offset + text_width;
      *display_width = (*display_width > field_width) ? field_width : *display_width;
   }
}