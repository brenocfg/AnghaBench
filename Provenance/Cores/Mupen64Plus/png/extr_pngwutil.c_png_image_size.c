#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
typedef  int png_alloc_size_t ;
struct TYPE_3__ {int height; int rowbytes; scalar_t__ interlaced; int width; unsigned int pixel_depth; } ;

/* Variables and functions */
 int PNG_PASS_COLS (int,int) ; 
 int PNG_PASS_ROWS (int,int) ; 
 int PNG_ROWBYTES (unsigned int,int) ; 

__attribute__((used)) static png_alloc_size_t
png_image_size(png_structrp png_ptr)
{
   /* Only return sizes up to the maximum of a png_uint_32; do this by limiting
    * the width and height used to 15 bits.
    */
   png_uint_32 h = png_ptr->height;

   if (png_ptr->rowbytes < 32768 && h < 32768)
   {
      if (png_ptr->interlaced != 0)
      {
         /* Interlacing makes the image larger because of the replication of
          * both the filter byte and the padding to a byte boundary.
          */
         png_uint_32 w = png_ptr->width;
         unsigned int pd = png_ptr->pixel_depth;
         png_alloc_size_t cb_base;
         int pass;

         for (cb_base=0, pass=0; pass<=6; ++pass)
         {
            png_uint_32 pw = PNG_PASS_COLS(w, pass);

            if (pw > 0)
               cb_base += (PNG_ROWBYTES(pd, pw)+1) * PNG_PASS_ROWS(h, pass);
         }

         return cb_base;
      }

      else
         return (png_ptr->rowbytes+1) * h;
   }

   else
      return 0xffffffffU;
}