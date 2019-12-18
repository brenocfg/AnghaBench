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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */

bool utf16_conv_utf8(uint8_t *out, size_t *out_chars,
     const uint16_t *in, size_t in_size)
{
   static uint8_t kUtf8Limits[5] = { 0xC0, 0xE0, 0xF0, 0xF8, 0xFC };
   size_t out_pos = 0;
   size_t in_pos  = 0;

   for (;;)
   {
      unsigned numAdds;
      uint32_t value;

      if (in_pos == in_size)
      {
         *out_chars = out_pos;
         return true;
      }
      value = in[in_pos++];
      if (value < 0x80)
      {
         if (out)
            out[out_pos] = (char)value;
         out_pos++;
         continue;
      }

      if (value >= 0xD800 && value < 0xE000)
      {
         uint32_t c2;

         if (value >= 0xDC00 || in_pos == in_size)
            break;
         c2 = in[in_pos++];
         if (c2 < 0xDC00 || c2 >= 0xE000)
            break;
         value = (((value - 0xD800) << 10) | (c2 - 0xDC00)) + 0x10000;
      }

      for (numAdds = 1; numAdds < 5; numAdds++)
         if (value < (((uint32_t)1) << (numAdds * 5 + 6)))
            break;
      if (out)
         out[out_pos] = (char)(kUtf8Limits[numAdds - 1]
               + (value >> (6 * numAdds)));
      out_pos++;
      do
      {
         numAdds--;
         if (out)
            out[out_pos] = (char)(0x80
                  + ((value >> (6 * numAdds)) & 0x3F));
         out_pos++;
      }while (numAdds != 0);
   }

   *out_chars = out_pos;
   return false;
}