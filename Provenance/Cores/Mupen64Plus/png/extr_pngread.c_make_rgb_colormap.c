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
 int /*<<< orphan*/  png_create_colormap_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
make_rgb_colormap(png_image_read_control *display)
{
   unsigned int i, r;

   /* Build a 6x6x6 opaque RGB cube */
   for (i=r=0; r<6; ++r)
   {
      unsigned int g;

      for (g=0; g<6; ++g)
      {
         unsigned int b;

         for (b=0; b<6; ++b)
            png_create_colormap_entry(display, i++, r*51, g*51, b*51, 255,
                P_sRGB);
      }
   }

   return (int)i;
}