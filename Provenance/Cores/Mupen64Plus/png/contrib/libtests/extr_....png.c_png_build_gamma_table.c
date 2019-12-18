#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* png_structrp ;
typedef  unsigned int png_byte ;
struct TYPE_11__ {scalar_t__ gamma; } ;
struct TYPE_10__ {unsigned int red; unsigned int green; unsigned int blue; unsigned int gray; } ;
struct TYPE_12__ {scalar_t__ screen_gamma; int transformations; int color_type; unsigned int gamma_shift; TYPE_2__ colorspace; int /*<<< orphan*/ * gamma_16_from_1; int /*<<< orphan*/ * gamma_16_to_1; int /*<<< orphan*/ * gamma_16_table; TYPE_1__ sig_bit; int /*<<< orphan*/ * gamma_from_1; int /*<<< orphan*/ * gamma_to_1; int /*<<< orphan*/ * gamma_table; } ;

/* Variables and functions */
 int PNG_16_TO_8 ; 
 int PNG_COLOR_MASK_COLOR ; 
 int PNG_COMPOSE ; 
 scalar_t__ PNG_FP_1 ; 
 unsigned int PNG_MAX_GAMMA_8 ; 
 int PNG_RGB_TO_GRAY ; 
 int PNG_SCALE_16_TO_8 ; 
 int /*<<< orphan*/  png_build_16bit_table (TYPE_3__*,int /*<<< orphan*/ **,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  png_build_16to8_table (TYPE_3__*,int /*<<< orphan*/ **,unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  png_build_8bit_table (TYPE_3__*,int /*<<< orphan*/ **,scalar_t__) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_destroy_gamma_table (TYPE_3__*) ; 
 scalar_t__ png_product2 (scalar_t__,scalar_t__) ; 
 scalar_t__ png_reciprocal (scalar_t__) ; 
 scalar_t__ png_reciprocal2 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  png_warning (TYPE_3__*,char*) ; 

void /* PRIVATE */
png_build_gamma_table(png_structrp png_ptr, int bit_depth)
{
   png_debug(1, "in png_build_gamma_table");

   /* Remove any existing table; this copes with multiple calls to
    * png_read_update_info. The warning is because building the gamma tables
    * multiple times is a performance hit - it's harmless but the ability to
    * call png_read_update_info() multiple times is new in 1.5.6 so it seems
    * sensible to warn if the app introduces such a hit.
    */
   if (png_ptr->gamma_table != NULL || png_ptr->gamma_16_table != NULL)
   {
      png_warning(png_ptr, "gamma table being rebuilt");
      png_destroy_gamma_table(png_ptr);
   }

   if (bit_depth <= 8)
   {
      png_build_8bit_table(png_ptr, &png_ptr->gamma_table,
          png_ptr->screen_gamma > 0 ?
          png_reciprocal2(png_ptr->colorspace.gamma,
          png_ptr->screen_gamma) : PNG_FP_1);

#if defined(PNG_READ_BACKGROUND_SUPPORTED) || \
   defined(PNG_READ_ALPHA_MODE_SUPPORTED) || \
   defined(PNG_READ_RGB_TO_GRAY_SUPPORTED)
      if ((png_ptr->transformations & (PNG_COMPOSE | PNG_RGB_TO_GRAY)) != 0)
      {
         png_build_8bit_table(png_ptr, &png_ptr->gamma_to_1,
             png_reciprocal(png_ptr->colorspace.gamma));

         png_build_8bit_table(png_ptr, &png_ptr->gamma_from_1,
             png_ptr->screen_gamma > 0 ?
             png_reciprocal(png_ptr->screen_gamma) :
             png_ptr->colorspace.gamma/* Probably doing rgb_to_gray */);
      }
#endif /* READ_BACKGROUND || READ_ALPHA_MODE || RGB_TO_GRAY */
   }
#ifdef PNG_16BIT_SUPPORTED
   else
   {
      png_byte shift, sig_bit;

      if ((png_ptr->color_type & PNG_COLOR_MASK_COLOR) != 0)
      {
         sig_bit = png_ptr->sig_bit.red;

         if (png_ptr->sig_bit.green > sig_bit)
            sig_bit = png_ptr->sig_bit.green;

         if (png_ptr->sig_bit.blue > sig_bit)
            sig_bit = png_ptr->sig_bit.blue;
      }
      else
         sig_bit = png_ptr->sig_bit.gray;

      /* 16-bit gamma code uses this equation:
       *
       *   ov = table[(iv & 0xff) >> gamma_shift][iv >> 8]
       *
       * Where 'iv' is the input color value and 'ov' is the output value -
       * pow(iv, gamma).
       *
       * Thus the gamma table consists of up to 256 256-entry tables.  The table
       * is selected by the (8-gamma_shift) most significant of the low 8 bits
       * of the color value then indexed by the upper 8 bits:
       *
       *   table[low bits][high 8 bits]
       *
       * So the table 'n' corresponds to all those 'iv' of:
       *
       *   <all high 8-bit values><n << gamma_shift>..<(n+1 << gamma_shift)-1>
       *
       */
      if (sig_bit > 0 && sig_bit < 16U)
         /* shift == insignificant bits */
         shift = (png_byte)((16U - sig_bit) & 0xff);

      else
         shift = 0; /* keep all 16 bits */

      if ((png_ptr->transformations & (PNG_16_TO_8 | PNG_SCALE_16_TO_8)) != 0)
      {
         /* PNG_MAX_GAMMA_8 is the number of bits to keep - effectively
          * the significant bits in the *input* when the output will
          * eventually be 8 bits.  By default it is 11.
          */
         if (shift < (16U - PNG_MAX_GAMMA_8))
            shift = (16U - PNG_MAX_GAMMA_8);
      }

      if (shift > 8U)
         shift = 8U; /* Guarantees at least one table! */

      png_ptr->gamma_shift = shift;

      /* NOTE: prior to 1.5.4 this test used to include PNG_BACKGROUND (now
       * PNG_COMPOSE).  This effectively smashed the background calculation for
       * 16-bit output because the 8-bit table assumes the result will be
       * reduced to 8 bits.
       */
      if ((png_ptr->transformations & (PNG_16_TO_8 | PNG_SCALE_16_TO_8)) != 0)
          png_build_16to8_table(png_ptr, &png_ptr->gamma_16_table, shift,
          png_ptr->screen_gamma > 0 ? png_product2(png_ptr->colorspace.gamma,
          png_ptr->screen_gamma) : PNG_FP_1);

      else
          png_build_16bit_table(png_ptr, &png_ptr->gamma_16_table, shift,
          png_ptr->screen_gamma > 0 ? png_reciprocal2(png_ptr->colorspace.gamma,
          png_ptr->screen_gamma) : PNG_FP_1);

#if defined(PNG_READ_BACKGROUND_SUPPORTED) || \
   defined(PNG_READ_ALPHA_MODE_SUPPORTED) || \
   defined(PNG_READ_RGB_TO_GRAY_SUPPORTED)
      if ((png_ptr->transformations & (PNG_COMPOSE | PNG_RGB_TO_GRAY)) != 0)
      {
         png_build_16bit_table(png_ptr, &png_ptr->gamma_16_to_1, shift,
             png_reciprocal(png_ptr->colorspace.gamma));

         /* Notice that the '16 from 1' table should be full precision, however
          * the lookup on this table still uses gamma_shift, so it can't be.
          * TODO: fix this.
          */
         png_build_16bit_table(png_ptr, &png_ptr->gamma_16_from_1, shift,
             png_ptr->screen_gamma > 0 ? png_reciprocal(png_ptr->screen_gamma) :
             png_ptr->colorspace.gamma/* Probably doing rgb_to_gray */);
      }
#endif /* READ_BACKGROUND || READ_ALPHA_MODE || RGB_TO_GRAY */
   }
#endif /* 16BIT */
}