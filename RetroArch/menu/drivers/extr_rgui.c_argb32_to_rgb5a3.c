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
typedef  unsigned int uint16_t ;

/* Variables and functions */

__attribute__((used)) static uint16_t argb32_to_rgb5a3(uint32_t col)
{
   /* Extract colour components */
   unsigned a = (col >> 24) & 0xff;
   unsigned r = (col >> 16) & 0xff;
   unsigned g = (col >> 8)  & 0xff;
   unsigned b = col & 0xff;
   unsigned a3 = a >> 5;
   if (a < 0xff)
   {
      /* Gekko platforms only have a 3 bit alpha channel, which
       * is one bit less than all 'standard' target platforms.
       * As a result, Gekko colours are effectively ~6-7% less
       * transparent than expected, which causes backgrounds and
       * borders to appear too bright. We therefore have to darken
       * each RGB component according to the difference between Gekko
       * alpha and normal 4 bit alpha values... */
      unsigned a4 = a >> 4;
      float a_factor = 1.0;
      if (a3 > 0)
      {
         /* Avoid divide by zero errors... */
         a_factor = ((float)a4 * (1.0 / 15.0)) / ((float)a3 * (1.0 / 7.0));
      }
      r = (unsigned)(((float)r * a_factor) + 0.5);
      g = (unsigned)(((float)g * a_factor) + 0.5);
      b = (unsigned)(((float)b * a_factor) + 0.5);
      /* a_factor can actually be greater than 1. This will never happen
       * with the current preset theme colour values, but users can set
       * any custom values they like, so we have to play it safe... */
      r = (r <= 0xff) ? r : 0xff;
      g = (g <= 0xff) ? g : 0xff;
      b = (b <= 0xff) ? b : 0xff;
   }
   /* Convert RGB from 8 bit to 4 bit */
   r = r >> 4;
   g = g >> 4;
   b = b >> 4;
   /* Return final value */
   return (a3 << 12) | (r << 8) | (g << 4) | b;
}