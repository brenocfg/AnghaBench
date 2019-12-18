#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  TYPE_3__* png_const_colorp ;
struct TYPE_12__ {int ir; int ig; int ib; int dr; int dg; int db; } ;
struct TYPE_14__ {int in_opaque; int output_8bit; int accumulate; int /*<<< orphan*/ * error_ptr; int /*<<< orphan*/ * error; TYPE_2__ background_color; TYPE_2__* background; int /*<<< orphan*/ * from_linear; void* transform; void* out_gp; void* in_gp; scalar_t__ is_palette; TYPE_5__ const* out_image; TYPE_5__* in_image; } ;
typedef  TYPE_4__ Transform ;
struct TYPE_11__ {int format; } ;
struct TYPE_15__ {int opts; TYPE_1__ image; } ;
struct TYPE_13__ {size_t red; size_t green; size_t blue; } ;
typedef  TYPE_5__ Image ;

/* Variables and functions */
 int ACCUMULATE ; 
 int BASE_FORMATS ; 
 int BUFFER_INIT8 ; 
 int PNG_FORMAT_FLAG_ALPHA ; 
 int PNG_FORMAT_FLAG_COLOR ; 
 int PNG_FORMAT_FLAG_COLORMAP ; 
 int PNG_FORMAT_FLAG_LINEAR ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int,int) ; 
 void* get_pixel (int) ; 
 int /*<<< orphan*/ *** gpc_error ; 
 int /*<<< orphan*/ *** gpc_error_to_colormap ; 
 int /*<<< orphan*/ *** gpc_error_via_linear ; 
 void*** gpc_fn ; 
 void*** gpc_fn_colormapped ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 void** sRGB_to_d ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
transform_from_formats(Transform *result, Image *in_image,
   const Image *out_image, png_const_colorp background, int via_linear)
{
   png_uint_32 in_format, out_format;
   png_uint_32 in_base, out_base;

   memset(result, 0, sizeof *result);

   /* Store the original images for error messages */
   result->in_image = in_image;
   result->out_image = out_image;

   in_format = in_image->image.format;
   out_format = out_image->image.format;

   if (in_format & PNG_FORMAT_FLAG_LINEAR)
      result->in_opaque = 65535;
   else
      result->in_opaque = 255;

   result->output_8bit = (out_format & PNG_FORMAT_FLAG_LINEAR) == 0;

   result->is_palette = 0; /* set by caller if required */
   result->accumulate = (in_image->opts & ACCUMULATE) != 0;

   /* The loaders (which need the ordering information) */
   result->in_gp = get_pixel(in_format);
   result->out_gp = get_pixel(out_format);

   /* Remove the ordering information: */
   in_format &= BASE_FORMATS | PNG_FORMAT_FLAG_COLORMAP;
   in_base = in_format & BASE_FORMATS;
   out_format &= BASE_FORMATS | PNG_FORMAT_FLAG_COLORMAP;
   out_base = out_format & BASE_FORMATS;

   if (via_linear)
   {
      /* Check for an error in this program: */
      if (out_format & (PNG_FORMAT_FLAG_LINEAR|PNG_FORMAT_FLAG_COLORMAP))
      {
         fprintf(stderr, "internal transform via linear error 0x%x->0x%x\n",
            in_format, out_format);
         exit(1);
      }

      result->transform = gpc_fn[in_base][out_base | PNG_FORMAT_FLAG_LINEAR];
      result->from_linear = gpc_fn[out_base | PNG_FORMAT_FLAG_LINEAR][out_base];
      result->error_ptr = gpc_error_via_linear[in_format][out_format];
   }

   else if (~in_format & out_format & PNG_FORMAT_FLAG_COLORMAP)
   {
      /* The input is not colormapped but the output is, the errors will
       * typically be large (only the grayscale-no-alpha case permits preserving
       * even 8-bit values.)
       */
      result->transform = gpc_fn[in_base][out_base];
      result->from_linear = NULL;
      result->error_ptr = gpc_error_to_colormap[in_base][out_base];
   }

   else
   {
      /* The caller handles the colormap->pixel value conversion, so the
       * transform function just gets a pixel value, however because libpng
       * currently contains a different implementation for mapping a colormap if
       * both input and output are colormapped we need different conversion
       * functions to deal with errors in the libpng implementation.
       */
      if (in_format & out_format & PNG_FORMAT_FLAG_COLORMAP)
         result->transform = gpc_fn_colormapped[in_base][out_base];
      else
         result->transform = gpc_fn[in_base][out_base];
      result->from_linear = NULL;
      result->error_ptr = gpc_error[in_format][out_format];
   }

   /* Follow the libpng simplified API rules to work out what to pass to the gpc
    * routines as a background value, if one is not required pass NULL so that
    * this program crashes in the even of a programming error.
    */
   result->background = NULL; /* default: not required */

   /* Rule 1: background only need be supplied if alpha is to be removed */
   if (in_format & ~out_format & PNG_FORMAT_FLAG_ALPHA)
   {
      /* The input value is 'NULL' to use the background and (otherwise) an sRGB
       * background color (to use a solid color).  The code above uses a fixed
       * byte value, BUFFER_INIT8, for buffer even for 16-bit output.  For
       * linear (16-bit) output the sRGB background color is ignored; the
       * composition is always on the background (so BUFFER_INIT8 * 257), except
       * that for the colormap (i.e. linear colormapped output) black is used.
       */
      result->background = &result->background_color;

      if (out_format & PNG_FORMAT_FLAG_LINEAR || via_linear)
      {
         if (out_format & PNG_FORMAT_FLAG_COLORMAP)
         {
            result->background_color.ir =
               result->background_color.ig =
               result->background_color.ib = 0;
            result->background_color.dr =
               result->background_color.dg =
               result->background_color.db = 0;
         }

         else
         {
            result->background_color.ir =
               result->background_color.ig =
               result->background_color.ib = BUFFER_INIT8 * 257;
            result->background_color.dr =
               result->background_color.dg =
               result->background_color.db = 0;
         }
      }

      else /* sRGB output */
      {
         if (background != NULL)
         {
            if (out_format & PNG_FORMAT_FLAG_COLOR)
            {
               result->background_color.ir = background->red;
               result->background_color.ig = background->green;
               result->background_color.ib = background->blue;
               /* TODO: sometimes libpng uses the power law conversion here, how
                * to handle this?
                */
               result->background_color.dr = sRGB_to_d[background->red];
               result->background_color.dg = sRGB_to_d[background->green];
               result->background_color.db = sRGB_to_d[background->blue];
            }

            else /* grayscale: libpng only looks at 'g' */
            {
               result->background_color.ir =
                  result->background_color.ig =
                  result->background_color.ib = background->green;
               /* TODO: sometimes libpng uses the power law conversion here, how
                * to handle this?
                */
               result->background_color.dr =
                  result->background_color.dg =
                  result->background_color.db = sRGB_to_d[background->green];
            }
         }

         else if ((out_format & PNG_FORMAT_FLAG_COLORMAP) == 0)
         {
            result->background_color.ir =
               result->background_color.ig =
               result->background_color.ib = BUFFER_INIT8;
            /* TODO: sometimes libpng uses the power law conversion here, how
             * to handle this?
             */
            result->background_color.dr =
               result->background_color.dg =
               result->background_color.db = sRGB_to_d[BUFFER_INIT8];
         }

         /* Else the output is colormapped and a background color must be
          * provided; if pngstest crashes then that is a bug in this program
          * (though libpng should png_error as well.)
          */
         else
            result->background = NULL;
      }
   }

   if (result->background == NULL)
   {
      result->background_color.ir =
         result->background_color.ig =
         result->background_color.ib = -1; /* not used */
      result->background_color.dr =
         result->background_color.dg =
         result->background_color.db = 1E30; /* not used */
   }


   /* Copy the error values into the Transform: */
   result->error[0] = result->error_ptr[0];
   result->error[1] = result->error_ptr[1];
   result->error[2] = result->error_ptr[2];
   result->error[3] = result->error_ptr[3];
}