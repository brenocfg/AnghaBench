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
typedef  int /*<<< orphan*/  png_image_read_control ;

/* Variables and functions */
 int /*<<< orphan*/  P_sRGB ; 
 int /*<<< orphan*/  png_create_colormap_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
make_ga_colormap(png_image_read_control *display)
{
   unsigned int i, a;

   /* Alpha is retained, the output will be a color-map with entries
    * selected by six levels of alpha.  One transparent entry, 6 gray
    * levels for all the intermediate alpha values, leaving 230 entries
    * for the opaque grays.  The color-map entries are the six values
    * [0..5]*51, the GA processing uses PNG_DIV51(value) to find the
    * relevant entry.
    *
    * if (alpha > 229) // opaque
    * {
    *    // The 231 entries are selected to make the math below work:
    *    base = 0;
    *    entry = (231 * gray + 128) >> 8;
    * }
    * else if (alpha < 26) // transparent
    * {
    *    base = 231;
    *    entry = 0;
    * }
    * else // partially opaque
    * {
    *    base = 226 + 6 * PNG_DIV51(alpha);
    *    entry = PNG_DIV51(gray);
    * }
    */
   i = 0;
   while (i < 231)
   {
      unsigned int gray = (i * 256 + 115) / 231;
      png_create_colormap_entry(display, i++, gray, gray, gray, 255, P_sRGB);
   }

   /* 255 is used here for the component values for consistency with the code
    * that undoes premultiplication in pngwrite.c.
    */
   png_create_colormap_entry(display, i++, 255, 255, 255, 0, P_sRGB);

   for (a=1; a<5; ++a)
   {
      unsigned int g;

      for (g=0; g<6; ++g)
         png_create_colormap_entry(display, i++, g*51, g*51, g*51, a*51,
             P_sRGB);
   }

   return (int)i;
}