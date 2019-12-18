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
struct sprite {unsigned int height; unsigned int width; scalar_t__* buffer; } ;
typedef  scalar_t__ png_uint_32 ;
typedef  scalar_t__ png_uint_16 ;
typedef  TYPE_1__* png_imagep ;
struct TYPE_3__ {unsigned int height; unsigned int width; } ;

/* Variables and functions */
 int /*<<< orphan*/  compose (int) ; 

__attribute__((used)) static void
sprite_op(const struct sprite *sprite, int x_offset, int y_offset,
   png_imagep image, const png_uint_16 *buffer)
{
   /* This is where the Porter-Duff 'Over' operator is evaluated; change this
    * code to change the operator (this could be parameterized).  Any other
    * image processing operation could be used here.
    */


   /* Check for an x or y offset that pushes any part of the image beyond the
    * right or bottom of the sprite:
    */
   if ((y_offset < 0 || (unsigned)/*SAFE*/y_offset < sprite->height) &&
       (x_offset < 0 || (unsigned)/*SAFE*/x_offset < sprite->width))
   {
      unsigned int y = 0;

      if (y_offset < 0)
         y = -y_offset; /* Skip to first visible row */

      do
      {
         unsigned int x = 0;

         if (x_offset < 0)
            x = -x_offset;

         do
         {
            /* In and out are RGBA values, so: */
            const png_uint_16 *in_pixel = buffer + (y * image->width + x)*4;
            png_uint_32 in_alpha = in_pixel[3];

            /* This is the optimized Porter-Duff 'Over' operation, when the
             * input alpha is 0 the output is not changed.
             */
            if (in_alpha > 0)
            {
               png_uint_16 *out_pixel = sprite->buffer +
                  ((y+y_offset) * sprite->width + (x+x_offset))*4;

               /* This is the weight to apply to the output: */
               in_alpha = 65535-in_alpha;

               if (in_alpha > 0)
               {
                  /* The input must be composed onto the output. This means
                   * multiplying the current output pixel value by the inverse
                   * of the input alpha (1-alpha). A division is required but
                   * it is by the constant 65535.  Approximate this as:
                   *
                   *     (x + (x >> 16) + 32769) >> 16;
                   *
                   * This is exact (and does not overflow) for all values of
                   * x in the range 0..65535*65535.  (Note that the calculation
                   * produces the closest integer; the maximum error is <0.5).
                   */
                  png_uint_32 tmp;

#                 define compose(c)\
                     tmp = out_pixel[c] * in_alpha;\
                     tmp = (tmp + (tmp >> 16) + 32769) >> 16;\
                     out_pixel[c] = tmp + in_pixel[c]

                  /* The following is very vectorizable... */
                  compose(0);
                  compose(1);
                  compose(2);
                  compose(3);
               }

               else
                  out_pixel[0] = in_pixel[0],
                  out_pixel[1] = in_pixel[1],
                  out_pixel[2] = in_pixel[2],
                  out_pixel[3] = in_pixel[3];
            }
         }
         while (++x < image->width);
      }
      while (++y < image->height);
   }
}