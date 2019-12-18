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
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t argb32_to_abgr1555(uint32_t col)
{
   /* Extract colour components */
   unsigned a = (col >> 24) & 0xff;
   unsigned r = (col >> 16) & 0xff;
   unsigned g = (col >> 8)  & 0xff;
   unsigned b = col & 0xff;
   if (a < 0xff)
   {
      /* Background and border colours are normally semi-transparent
       * (so we can see suspended content when opening the quick menu).
       * When no content is loaded, the 'image' behind the RGUI background
       * and border is black - which has the effect of darkening the
       * perceived background/border colours. All the preset theme (and
       * default 'custom') colour values have been adjusted to account for
       * this, but abgr1555 only has a 1 bit alpha channel. This means all
       * colours become fully opaque, and consequently backgrounds/borders
       * become abnormally bright.
       * We therefore have to darken each RGB value according to the alpha
       * component of the input colour... */
      float a_factor = (float)a * (1.0 / 255.0);
      r = (unsigned)(((float)r * a_factor) + 0.5) & 0xff;
      g = (unsigned)(((float)g * a_factor) + 0.5) & 0xff;
      b = (unsigned)(((float)b * a_factor) + 0.5) & 0xff;
   }
   /* Convert from 8 bit to 5 bit */
   r = r >> 3;
   g = g >> 3;
   b = b >> 3;
   /* Return final value - alpha always set to 1 */
   return (1 << 15) | (b << 10) | (g << 5) | r;
}