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
typedef  int /*<<< orphan*/  png_const_bytep ;
typedef  scalar_t__ png_colorp ;
typedef  scalar_t__ png_bytep ;

/* Variables and functions */
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  set_color (scalar_t__,scalar_t__,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int xyinterp (unsigned int,unsigned int,int,int,int,int) ; 

__attribute__((used)) static int
generate_palette(png_colorp palette, png_bytep trans, int bit_depth,
   png_const_bytep gamma_table, unsigned int *colors)
{
   /*
    * 1-bit: entry 0 is transparent-red, entry 1 is opaque-white
    * 2-bit: entry 0: transparent-green
    *        entry 1: 40%-red
    *        entry 2: 80%-blue
    *        entry 3: opaque-white
    * 4-bit: the 16 combinations of the 2-bit case
    * 8-bit: the 256 combinations of the 4-bit case
    */
   switch (colors[0])
   {
      default:
         fprintf(stderr, "makepng: --colors=...: invalid count %u\n",
            colors[0]);
         exit(1);

      case 1:
         set_color(palette+0, trans+0, colors[1], colors[1], colors[1], 255,
            gamma_table);
         return 1;

      case 2:
         set_color(palette+0, trans+0, colors[1], colors[1], colors[1],
            colors[2], gamma_table);
         return 1;

      case 3:
         set_color(palette+0, trans+0, colors[1], colors[2], colors[3], 255,
            gamma_table);
         return 1;

      case 4:
         set_color(palette+0, trans+0, colors[1], colors[2], colors[3],
            colors[4], gamma_table);
         return 1;

      case 0:
         if (bit_depth == 1)
         {
            set_color(palette+0, trans+0, 255, 0, 0, 0, gamma_table);
            set_color(palette+1, trans+1, 255, 255, 255, 255, gamma_table);
            return 2;
         }

         else
         {
            unsigned int size = 1U << (bit_depth/2); /* 2, 4 or 16 */
            unsigned int x, y;
            volatile unsigned int ip = 0;

            for (x=0; x<size; ++x) for (y=0; y<size; ++y)
            {
               ip = x + (size * y);

               /* size is at most 16, so the scaled value below fits in 16 bits
                */
#              define interp(pos, c1, c2) ((pos * c1) + ((size-pos) * c2))
#              define xyinterp(x, y, c1, c2, c3, c4) (((size * size / 2) +\
                  (interp(x, c1, c2) * y + (size-y) * interp(x, c3, c4))) /\
                  (size*size))

               set_color(palette+ip, trans+ip,
                  /* color:    green, red,blue,white */
                  xyinterp(x, y,   0, 255,   0, 255),
                  xyinterp(x, y, 255,   0,   0, 255),
                  xyinterp(x, y,   0,   0, 255, 255),
                  /* alpha:        0, 102, 204, 255) */
                  xyinterp(x, y,   0, 102, 204, 255),
                  gamma_table);
            }

            return ip+1;
         }
   }
}