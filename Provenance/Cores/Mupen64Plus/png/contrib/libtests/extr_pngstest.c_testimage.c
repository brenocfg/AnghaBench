#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  int /*<<< orphan*/ * png_colorp ;
typedef  int /*<<< orphan*/  png_color ;
typedef  int /*<<< orphan*/  format_list ;
struct TYPE_13__ {int format; } ;
struct TYPE_14__ {int opts; TYPE_1__ image; scalar_t__* tmpfile_name; scalar_t__ input_memory_size; int /*<<< orphan*/ * input_memory; int /*<<< orphan*/ * input_file; scalar_t__ allocsize; scalar_t__ bufsize; int /*<<< orphan*/ * buffer; } ;
typedef  TYPE_2__ Image ;

/* Variables and functions */
 int FORMAT_COUNT ; 
 int PNG_FORMAT_FLAG_ALPHA ; 
 int PNG_FORMAT_FLAG_COLORMAP ; 
 int PNG_FORMAT_FLAG_LINEAR ; 
 int /*<<< orphan*/  checkopaque (TYPE_2__*) ; 
 int compare_two_images (TYPE_2__*,TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 scalar_t__ format_isset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  freeimage (TYPE_2__*) ; 
 int /*<<< orphan*/  newimage (TYPE_2__*) ; 
 int /*<<< orphan*/  random_color (int /*<<< orphan*/ *) ; 
 int read_file (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  resetimage (TYPE_2__*) ; 
 int write_one_file (TYPE_2__*,TYPE_2__*,int) ; 

__attribute__((used)) static int
testimage(Image *image, png_uint_32 opts, format_list *pf)
{
   int result;
   Image copy;

   /* Copy the original data, stealing it from 'image' */
   checkopaque(image);
   copy = *image;

   copy.opts = opts;
   copy.buffer = NULL;
   copy.bufsize = 0;
   copy.allocsize = 0;

   image->input_file = NULL;
   image->input_memory = NULL;
   image->input_memory_size = 0;
   image->tmpfile_name[0] = 0;

   {
      png_uint_32 counter;
      Image output;

      newimage(&output);

      result = 1;

      /* Use the low bit of 'counter' to indicate whether or not to do alpha
       * removal with a background color or by composting onto the image; this
       * step gets skipped if it isn't relevant
       */
      for (counter=0; counter<2*FORMAT_COUNT; ++counter)
         if (format_isset(pf, counter >> 1))
      {
         png_uint_32 format = counter >> 1;

         png_color background_color;
         png_colorp background = NULL;

         /* If there is a format change that removes the alpha channel then
          * the background is relevant.  If the output is 8-bit color-mapped
          * then a background color *must* be provided, otherwise there are
          * two tests to do - one with a color, the other with NULL.  The
          * NULL test happens second.
          */
         if ((counter & 1) == 0)
         {
            if ((format & PNG_FORMAT_FLAG_ALPHA) == 0 &&
               (image->image.format & PNG_FORMAT_FLAG_ALPHA) != 0)
            {
               /* Alpha/transparency will be removed, the background is
                * relevant: make it a color the first time
                */
               random_color(&background_color);
               background = &background_color;

               /* BUT if the output is to a color-mapped 8-bit format then
                * the background must always be a color, so increment 'counter'
                * to skip the NULL test.
                */
               if ((format & PNG_FORMAT_FLAG_COLORMAP) != 0 &&
                  (format & PNG_FORMAT_FLAG_LINEAR) == 0)
                  ++counter;
            }

            /* Otherwise an alpha channel is not being eliminated, just leave
             * background NULL and skip the (counter & 1) NULL test.
             */
            else
               ++counter;
         }
         /* else just use NULL for background */

         resetimage(&copy);
         copy.opts = opts; /* in case read_file needs to change it */

         result = read_file(&copy, format, background);
         if (!result)
            break;

         /* Make sure the file just read matches the original file. */
         result = compare_two_images(image, &copy, 0/*via linear*/, background);
         if (!result)
            break;

#        ifdef PNG_SIMPLIFIED_WRITE_SUPPORTED
            /* Write the *copy* just made to a new file to make sure the write
             * side works ok.  Check the conversion to sRGB if the copy is
             * linear.
             */
            output.opts = opts;
            result = write_one_file(&output, &copy, 0/*convert to 8bit*/);
            if (!result)
               break;

            /* Validate against the original too; the background is needed here
             * as well so that compare_two_images knows what color was used.
             */
            result = compare_two_images(image, &output, 0, background);
            if (!result)
               break;

            if ((format & PNG_FORMAT_FLAG_LINEAR) != 0 &&
               (format & PNG_FORMAT_FLAG_COLORMAP) == 0)
            {
               /* 'output' is linear, convert to the corresponding sRGB format.
                */
               output.opts = opts;
               result = write_one_file(&output, &copy, 1/*convert to 8bit*/);
               if (!result)
                  break;

               /* This may involve a conversion via linear; in the ideal world
                * this would round-trip correctly, but libpng 1.5.7 is not the
                * ideal world so allow a drift (error_via_linear).
                *
                * 'image' has an alpha channel but 'output' does not then there
                * will a strip-alpha-channel operation (because 'output' is
                * linear), handle this by composing on black when doing the
                * comparison.
                */
               result = compare_two_images(image, &output, 1/*via_linear*/,
                  background);
               if (!result)
                  break;
            }
#        endif /* PNG_SIMPLIFIED_WRITE_SUPPORTED */
      }

      freeimage(&output);
   }

   freeimage(&copy);

   return result;
}