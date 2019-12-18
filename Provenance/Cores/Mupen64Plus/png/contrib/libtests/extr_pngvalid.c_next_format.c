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
typedef  int* png_bytep ;
typedef  int png_byte ;

/* Variables and functions */
 unsigned int PALETTE_COUNT (int) ; 

__attribute__((used)) static int
next_format(png_bytep colour_type, png_bytep bit_depth,
   unsigned int* palette_number, int low_depth_gray, int tRNS)
{
   if (*bit_depth == 0)
   {
      *colour_type = 0;
      if (low_depth_gray)
         *bit_depth = 1;
      else
         *bit_depth = 8;
      *palette_number = 0;
      return 1;
   }

   if  (*colour_type < 4/*no alpha channel*/)
   {
      /* Add multiple palettes for colour type 3, one image with tRNS
       * and one without for other non-alpha formats:
       */
      unsigned int pn = ++*palette_number;
      png_byte ct = *colour_type;

      if (((ct == 0/*GRAY*/ || ct/*RGB*/ == 2) && tRNS && pn < 2) ||
          (ct == 3/*PALETTE*/ && pn < PALETTE_COUNT(*bit_depth)))
         return 1;

      /* No: next bit depth */
      *palette_number = 0;
   }

   *bit_depth = (png_byte)(*bit_depth << 1);

   /* Palette images are restricted to 8 bit depth */
   if (*bit_depth <= 8
#ifdef DO_16BIT
         || (*colour_type != 3 && *bit_depth <= 16)
#endif
      )
      return 1;

   /* Move to the next color type, or return 0 at the end. */
   switch (*colour_type)
   {
      case 0:
         *colour_type = 2;
         *bit_depth = 8;
         return 1;

      case 2:
         *colour_type = 3;
         *bit_depth = 1;
         return 1;

      case 3:
         *colour_type = 4;
         *bit_depth = 8;
         return 1;

      case 4:
         *colour_type = 6;
         *bit_depth = 8;
         return 1;

      default:
         return 0;
   }
}