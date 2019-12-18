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
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/  png_store ;
typedef  int /*<<< orphan*/  png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  DEPTH (int) ; 
 int /*<<< orphan*/  PNG_INTERLACE_ADAM7 ; 
 int /*<<< orphan*/  PNG_INTERLACE_NONE ; 
 int /*<<< orphan*/  make_size_image (int /*<<< orphan*/ * const,int /*<<< orphan*/  const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static void
make_size(png_store* const ps, png_byte const colour_type, int bdlo,
    int const bdhi)
{
   for (; bdlo <= bdhi; ++bdlo)
   {
      png_uint_32 width;

      for (width = 1; width <= 16; ++width)
      {
         png_uint_32 height;

         for (height = 1; height <= 16; ++height)
         {
            /* The four combinations of DIY interlace and interlace or not -
             * no interlace + DIY should be identical to no interlace with
             * libpng doing it.
             */
            make_size_image(ps, colour_type, DEPTH(bdlo), PNG_INTERLACE_NONE,
               width, height, 0);
            make_size_image(ps, colour_type, DEPTH(bdlo), PNG_INTERLACE_NONE,
               width, height, 1);
#        ifdef PNG_WRITE_INTERLACING_SUPPORTED
            make_size_image(ps, colour_type, DEPTH(bdlo), PNG_INTERLACE_ADAM7,
               width, height, 0);
#        endif
#        if CAN_WRITE_INTERLACE
            /* 1.7.0 removes the hack that prevented app write of an interlaced
             * image if WRITE_INTERLACE was not supported
             */
            make_size_image(ps, colour_type, DEPTH(bdlo), PNG_INTERLACE_ADAM7,
               width, height, 1);
#        endif
         }
      }
   }
}