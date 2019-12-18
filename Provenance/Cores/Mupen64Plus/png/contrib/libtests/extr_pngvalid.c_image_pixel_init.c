#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* store_palette ;
typedef  int /*<<< orphan*/  png_uint_32 ;
typedef  int /*<<< orphan*/  png_const_bytep ;
typedef  int png_byte ;
struct TYPE_8__ {unsigned int palette_index; unsigned int red; unsigned int green; unsigned int blue; unsigned int alpha; int red_sBIT; int green_sBIT; int blue_sBIT; int alpha_sBIT; int colour_type; int bit_depth; int sample_depth; int /*<<< orphan*/  sig_bits; int /*<<< orphan*/  littleendian; int /*<<< orphan*/  swap16; scalar_t__ mono_inverted; scalar_t__ alpha_inverted; scalar_t__ alpha_first; scalar_t__ swap_rgb; scalar_t__ have_tRNS; } ;
typedef  TYPE_2__ image_pixel ;
struct TYPE_7__ {unsigned int red; unsigned int green; unsigned int blue; unsigned int alpha; } ;

/* Variables and functions */
 int PNG_COLOR_TYPE_PALETTE ; 
 int /*<<< orphan*/  image_pixel_setf (TYPE_2__*,unsigned int,unsigned int,unsigned int,unsigned int) ; 
 void* sample (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,unsigned int,int const,int const) ; 

__attribute__((used)) static void
image_pixel_init(image_pixel *this, png_const_bytep row, png_byte colour_type,
    png_byte bit_depth, png_uint_32 x, store_palette palette,
    const image_pixel *format /*from pngvalid transform of input*/)
{
   const png_byte sample_depth = (png_byte)(colour_type ==
      PNG_COLOR_TYPE_PALETTE ? 8 : bit_depth);
   const unsigned int max = (1U<<sample_depth)-1;
   const int swap16 = (format != 0 && format->swap16);
   const int littleendian = (format != 0 && format->littleendian);
   const int sig_bits = (format != 0 && format->sig_bits);

   /* Initially just set everything to the same number and the alpha to opaque.
    * Note that this currently assumes a simple palette where entry x has colour
    * rgb(x,x,x)!
    */
   this->palette_index = this->red = this->green = this->blue =
      sample(row, colour_type, bit_depth, x, 0, swap16, littleendian);
   this->alpha = max;
   this->red_sBIT = this->green_sBIT = this->blue_sBIT = this->alpha_sBIT =
      sample_depth;

   /* Then override as appropriate: */
   if (colour_type == 3) /* palette */
   {
      /* This permits the caller to default to the sample value. */
      if (palette != 0)
      {
         const unsigned int i = this->palette_index;

         this->red = palette[i].red;
         this->green = palette[i].green;
         this->blue = palette[i].blue;
         this->alpha = palette[i].alpha;
      }
   }

   else /* not palette */
   {
      unsigned int i = 0;

      if ((colour_type & 4) != 0 && format != 0 && format->alpha_first)
      {
         this->alpha = this->red;
         /* This handles the gray case for 'AG' pixels */
         this->palette_index = this->red = this->green = this->blue =
            sample(row, colour_type, bit_depth, x, 1, swap16, littleendian);
         i = 1;
      }

      if (colour_type & 2)
      {
         /* Green is second for both BGR and RGB: */
         this->green = sample(row, colour_type, bit_depth, x, ++i, swap16,
                 littleendian);

         if (format != 0 && format->swap_rgb) /* BGR */
             this->red = sample(row, colour_type, bit_depth, x, ++i, swap16,
                     littleendian);
         else
             this->blue = sample(row, colour_type, bit_depth, x, ++i, swap16,
                     littleendian);
      }

      else /* grayscale */ if (format != 0 && format->mono_inverted)
         this->red = this->green = this->blue = this->red ^ max;

      if ((colour_type & 4) != 0) /* alpha */
      {
         if (format == 0 || !format->alpha_first)
             this->alpha = sample(row, colour_type, bit_depth, x, ++i, swap16,
                     littleendian);

         if (format != 0 && format->alpha_inverted)
            this->alpha ^= max;
      }
   }

   /* Calculate the scaled values, these are simply the values divided by
    * 'max' and the error is initialized to the double precision epsilon value
    * from the header file.
    */
   image_pixel_setf(this,
      sig_bits ? (1U << format->red_sBIT)-1 : max,
      sig_bits ? (1U << format->green_sBIT)-1 : max,
      sig_bits ? (1U << format->blue_sBIT)-1 : max,
      sig_bits ? (1U << format->alpha_sBIT)-1 : max);

   /* Store the input information for use in the transforms - these will
    * modify the information.
    */
   this->colour_type = colour_type;
   this->bit_depth = bit_depth;
   this->sample_depth = sample_depth;
   this->have_tRNS = 0;
   this->swap_rgb = 0;
   this->alpha_first = 0;
   this->alpha_inverted = 0;
   this->mono_inverted = 0;
   this->swap16 = 0;
   this->littleendian = 0;
   this->sig_bits = 0;
}