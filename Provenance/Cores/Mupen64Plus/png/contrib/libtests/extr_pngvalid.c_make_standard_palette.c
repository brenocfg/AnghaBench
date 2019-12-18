#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {size_t alpha; size_t red; size_t green; size_t blue; } ;
typedef  TYPE_1__ store_palette_entry ;
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  png_store ;
typedef  size_t png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  make_four_random_bytes (int*,size_t*) ; 
 int /*<<< orphan*/  memset (size_t*,int,int) ; 
 TYPE_1__* store_write_palette (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static store_palette_entry *
make_standard_palette(png_store* ps, int npalette, int do_tRNS)
{
   static png_uint_32 palette_seed[2] = { 0x87654321, 9 };

   int i = 0;
   png_byte values[256][4];

   /* Always put in black and white plus the six primary and secondary colors.
    */
   for (; i<8; ++i)
   {
      values[i][1] = (png_byte)((i&1) ? 255U : 0U);
      values[i][2] = (png_byte)((i&2) ? 255U : 0U);
      values[i][3] = (png_byte)((i&4) ? 255U : 0U);
   }

   /* Then add 62 grays (one quarter of the remaining 256 slots). */
   {
      int j = 0;
      png_byte random_bytes[4];
      png_byte need[256];

      need[0] = 0; /*got black*/
      memset(need+1, 1, (sizeof need)-2); /*need these*/
      need[255] = 0; /*but not white*/

      while (i<70)
      {
         png_byte b;

         if (j==0)
         {
            make_four_random_bytes(palette_seed, random_bytes);
            j = 4;
         }

         b = random_bytes[--j];
         if (need[b])
         {
            values[i][1] = b;
            values[i][2] = b;
            values[i++][3] = b;
         }
      }
   }

   /* Finally add 192 colors at random - don't worry about matches to things we
    * already have, chance is less than 1/65536.  Don't worry about grays,
    * chance is the same, so we get a duplicate or extra gray less than 1 time
    * in 170.
    */
   for (; i<256; ++i)
      make_four_random_bytes(palette_seed, values[i]);

   /* Fill in the alpha values in the first byte.  Just use all possible values
    * (0..255) in an apparently random order:
    */
   {
      store_palette_entry *palette;
      png_byte selector[4];

      make_four_random_bytes(palette_seed, selector);

      if (do_tRNS)
         for (i=0; i<256; ++i)
            values[i][0] = (png_byte)(i ^ selector[0]);

      else
         for (i=0; i<256; ++i)
            values[i][0] = 255; /* no transparency/tRNS chunk */

      /* 'values' contains 256 ARGB values, but we only need 'npalette'.
       * 'npalette' will always be a power of 2: 2, 4, 16 or 256.  In the low
       * bit depth cases select colors at random, else it is difficult to have
       * a set of low bit depth palette test with any chance of a reasonable
       * range of colors.  Do this by randomly permuting values into the low
       * 'npalette' entries using an XOR mask generated here.  This also
       * permutes the npalette == 256 case in a potentially useful way (there is
       * no relationship between palette index and the color value therein!)
       */
      palette = store_write_palette(ps, npalette);

      for (i=0; i<npalette; ++i)
      {
         palette[i].alpha = values[i ^ selector[1]][0];
         palette[i].red   = values[i ^ selector[1]][1];
         palette[i].green = values[i ^ selector[1]][2];
         palette[i].blue  = values[i ^ selector[1]][3];
      }

      return palette;
   }
}