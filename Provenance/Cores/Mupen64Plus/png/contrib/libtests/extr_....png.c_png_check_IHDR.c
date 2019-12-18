#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  TYPE_1__* png_const_structrp ;
struct TYPE_5__ {int user_width_max; int user_height_max; int mode; int mng_features_permitted; } ;

/* Variables and functions */
 int PNG_COLOR_TYPE_GRAY_ALPHA ; 
 int PNG_COLOR_TYPE_PALETTE ; 
 int PNG_COLOR_TYPE_RGB ; 
 int PNG_COLOR_TYPE_RGB_ALPHA ; 
 int PNG_COMPRESSION_TYPE_BASE ; 
 int PNG_FILTER_TYPE_BASE ; 
 int PNG_FLAG_MNG_FILTER_64 ; 
 int PNG_HAVE_PNG_SIGNATURE ; 
 int PNG_INTERLACE_LAST ; 
 int PNG_INTRAPIXEL_DIFFERENCING ; 
 int PNG_SIZE_MAX ; 
 int PNG_UINT_31_MAX ; 
 int PNG_USER_HEIGHT_MAX ; 
 int PNG_USER_WIDTH_MAX ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 scalar_t__ png_gt (int,int) ; 
 int /*<<< orphan*/  png_warning (TYPE_1__*,char*) ; 

void /* PRIVATE */
png_check_IHDR(png_const_structrp png_ptr,
    png_uint_32 width, png_uint_32 height, int bit_depth,
    int color_type, int interlace_type, int compression_type,
    int filter_type)
{
   int error = 0;

   /* Check for width and height valid values */
   if (width == 0)
   {
      png_warning(png_ptr, "Image width is zero in IHDR");
      error = 1;
   }

   if (width > PNG_UINT_31_MAX)
   {
      png_warning(png_ptr, "Invalid image width in IHDR");
      error = 1;
   }

   if (png_gt(((width + 7) & (~7U)),
       ((PNG_SIZE_MAX
           - 48        /* big_row_buf hack */
           - 1)        /* filter byte */
           / 8)        /* 8-byte RGBA pixels */
           - 1))       /* extra max_pixel_depth pad */
   {
      /* The size of the row must be within the limits of this architecture.
       * Because the read code can perform arbitrary transformations the
       * maximum size is checked here.  Because the code in png_read_start_row
       * adds extra space "for safety's sake" in several places a conservative
       * limit is used here.
       *
       * NOTE: it would be far better to check the size that is actually used,
       * but the effect in the real world is minor and the changes are more
       * extensive, therefore much more dangerous and much more difficult to
       * write in a way that avoids compiler warnings.
       */
      png_warning(png_ptr, "Image width is too large for this architecture");
      error = 1;
   }

#ifdef PNG_SET_USER_LIMITS_SUPPORTED
   if (width > png_ptr->user_width_max)
#else
   if (width > PNG_USER_WIDTH_MAX)
#endif
   {
      png_warning(png_ptr, "Image width exceeds user limit in IHDR");
      error = 1;
   }

   if (height == 0)
   {
      png_warning(png_ptr, "Image height is zero in IHDR");
      error = 1;
   }

   if (height > PNG_UINT_31_MAX)
   {
      png_warning(png_ptr, "Invalid image height in IHDR");
      error = 1;
   }

#ifdef PNG_SET_USER_LIMITS_SUPPORTED
   if (height > png_ptr->user_height_max)
#else
   if (height > PNG_USER_HEIGHT_MAX)
#endif
   {
      png_warning(png_ptr, "Image height exceeds user limit in IHDR");
      error = 1;
   }

   /* Check other values */
   if (bit_depth != 1 && bit_depth != 2 && bit_depth != 4 &&
       bit_depth != 8 && bit_depth != 16)
   {
      png_warning(png_ptr, "Invalid bit depth in IHDR");
      error = 1;
   }

   if (color_type < 0 || color_type == 1 ||
       color_type == 5 || color_type > 6)
   {
      png_warning(png_ptr, "Invalid color type in IHDR");
      error = 1;
   }

   if (((color_type == PNG_COLOR_TYPE_PALETTE) && bit_depth > 8) ||
       ((color_type == PNG_COLOR_TYPE_RGB ||
         color_type == PNG_COLOR_TYPE_GRAY_ALPHA ||
         color_type == PNG_COLOR_TYPE_RGB_ALPHA) && bit_depth < 8))
   {
      png_warning(png_ptr, "Invalid color type/bit depth combination in IHDR");
      error = 1;
   }

   if (interlace_type >= PNG_INTERLACE_LAST)
   {
      png_warning(png_ptr, "Unknown interlace method in IHDR");
      error = 1;
   }

   if (compression_type != PNG_COMPRESSION_TYPE_BASE)
   {
      png_warning(png_ptr, "Unknown compression method in IHDR");
      error = 1;
   }

#ifdef PNG_MNG_FEATURES_SUPPORTED
   /* Accept filter_method 64 (intrapixel differencing) only if
    * 1. Libpng was compiled with PNG_MNG_FEATURES_SUPPORTED and
    * 2. Libpng did not read a PNG signature (this filter_method is only
    *    used in PNG datastreams that are embedded in MNG datastreams) and
    * 3. The application called png_permit_mng_features with a mask that
    *    included PNG_FLAG_MNG_FILTER_64 and
    * 4. The filter_method is 64 and
    * 5. The color_type is RGB or RGBA
    */
   if ((png_ptr->mode & PNG_HAVE_PNG_SIGNATURE) != 0 &&
       png_ptr->mng_features_permitted != 0)
      png_warning(png_ptr, "MNG features are not allowed in a PNG datastream");

   if (filter_type != PNG_FILTER_TYPE_BASE)
   {
      if (!((png_ptr->mng_features_permitted & PNG_FLAG_MNG_FILTER_64) != 0 &&
          (filter_type == PNG_INTRAPIXEL_DIFFERENCING) &&
          ((png_ptr->mode & PNG_HAVE_PNG_SIGNATURE) == 0) &&
          (color_type == PNG_COLOR_TYPE_RGB ||
          color_type == PNG_COLOR_TYPE_RGB_ALPHA)))
      {
         png_warning(png_ptr, "Unknown filter method in IHDR");
         error = 1;
      }

      if ((png_ptr->mode & PNG_HAVE_PNG_SIGNATURE) != 0)
      {
         png_warning(png_ptr, "Invalid filter method in IHDR");
         error = 1;
      }
   }

#else
   if (filter_type != PNG_FILTER_TYPE_BASE)
   {
      png_warning(png_ptr, "Unknown filter method in IHDR");
      error = 1;
   }
#endif

   if (error == 1)
      png_error(png_ptr, "Invalid IHDR data");
}