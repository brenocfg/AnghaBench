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
 int /*<<< orphan*/  outp (int,unsigned char) ; 

__attribute__((used)) static void vga_upload_palette(void)
{
   unsigned i;
   unsigned char r = 0;
   unsigned char g = 0;
   unsigned char b = 0;

   outp(0x03c8, 0);

   /* RGB332 */
   for (i = 0; i < 256; i++)
   {
      if (i > 0 && i % 64 == 0)
      {
         r = 0;
         g = 0;
         b++;
      }
      else if (i > 0 && i % 8 == 0)
      {
         r = 0;
         g++;
      }

      outp(0x03c9, r * (63.0f / 7.0f));
      outp(0x03c9, g * (63.0f / 7.0f));
      outp(0x03c9, b * (63.0f / 3.0f));

      r++;
   }
}