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
typedef  int /*<<< orphan*/  png_image_read_control ;

/* Variables and functions */
 int PNG_sRGB_FROM_LINEAR (int) ; 
 int P_LINEAR ; 
 int decode_gamma (int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static png_uint_32
png_colormap_compose(png_image_read_control *display,
    png_uint_32 foreground, int foreground_encoding, png_uint_32 alpha,
    png_uint_32 background, int encoding)
{
   /* The file value is composed on the background, the background has the given
    * encoding and so does the result, the file is encoded with P_FILE and the
    * file and alpha are 8-bit values.  The (output) encoding will always be
    * P_LINEAR or P_sRGB.
    */
   png_uint_32 f = decode_gamma(display, foreground, foreground_encoding);
   png_uint_32 b = decode_gamma(display, background, encoding);

   /* The alpha is always an 8-bit value (it comes from the palette), the value
    * scaled by 255 is what PNG_sRGB_FROM_LINEAR requires.
    */
   f = f * alpha + b * (255-alpha);

   if (encoding == P_LINEAR)
   {
      /* Scale to 65535; divide by 255, approximately (in fact this is extremely
       * accurate, it divides by 255.00000005937181414556, with no overflow.)
       */
      f *= 257; /* Now scaled by 65535 */
      f += f >> 16;
      f = (f+32768) >> 16;
   }

   else /* P_sRGB */
      f = PNG_sRGB_FROM_LINEAR(f);

   return f;
}