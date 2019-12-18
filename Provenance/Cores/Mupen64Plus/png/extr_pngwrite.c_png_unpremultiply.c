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
typedef  int png_byte ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_sRGB_FROM_LINEAR (int) ; 

__attribute__((used)) static png_byte
png_unpremultiply(png_uint_32 component, png_uint_32 alpha,
    png_uint_32 reciprocal/*from the above macro*/)
{
   /* The following gives 1.0 for an alpha of 0, which is fine, otherwise if 0/0
    * is represented as some other value there is more likely to be a
    * discontinuity which will probably damage compression when moving from a
    * fully transparent area to a nearly transparent one.  (The assumption here
    * is that opaque areas tend not to be 0 intensity.)
    *
    * There is a rounding problem here; if alpha is less than 128 it will end up
    * as 0 when scaled to 8 bits.  To avoid introducing spurious colors into the
    * output change for this too.
    */
   if (component >= alpha || alpha < 128)
      return 255;

   /* component<alpha, so component/alpha is less than one and
    * component*reciprocal is less than 2^31.
    */
   else if (component > 0)
   {
      /* The test is that alpha/257 (rounded) is less than 255, the first value
       * that becomes 255 is 65407.
       * NOTE: this must agree with the PNG_DIV257 macro (which must, therefore,
       * be exact!)  [Could also test reciprocal != 0]
       */
      if (alpha < 65407)
      {
         component *= reciprocal;
         component += 64; /* round to nearest */
         component >>= 7;
      }

      else
         component *= 255;

      /* Convert the component to sRGB. */
      return (png_byte)PNG_sRGB_FROM_LINEAR(component);
   }

   else
      return 0;
}