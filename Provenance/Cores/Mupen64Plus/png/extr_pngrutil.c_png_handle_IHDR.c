#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
typedef  int /*<<< orphan*/  png_inforp ;
typedef  void* png_byte ;
struct TYPE_8__ {int mode; int width; int height; int bit_depth; int color_type; int channels; scalar_t__ rowbytes; void* pixel_depth; void* compression_type; void* filter_type; void* interlaced; } ;

/* Variables and functions */
#define  PNG_COLOR_TYPE_GRAY 132 
#define  PNG_COLOR_TYPE_GRAY_ALPHA 131 
#define  PNG_COLOR_TYPE_PALETTE 130 
#define  PNG_COLOR_TYPE_RGB 129 
#define  PNG_COLOR_TYPE_RGB_ALPHA 128 
 int PNG_HAVE_IHDR ; 
 scalar_t__ PNG_ROWBYTES (void*,int) ; 
 int /*<<< orphan*/  png_chunk_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_crc_finish (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_crc_read (TYPE_1__*,void**,int) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_debug1 (int,char*,unsigned long) ; 
 int png_get_uint_31 (TYPE_1__*,void**) ; 
 int /*<<< orphan*/  png_set_IHDR (TYPE_1__*,int /*<<< orphan*/ ,int,int,int,int,int,int,int) ; 

void /* PRIVATE */
png_handle_IHDR(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
   png_byte buf[13];
   png_uint_32 width, height;
   int bit_depth, color_type, compression_type, filter_type;
   int interlace_type;

   png_debug(1, "in png_handle_IHDR");

   if ((png_ptr->mode & PNG_HAVE_IHDR) != 0)
      png_chunk_error(png_ptr, "out of place");

   /* Check the length */
   if (length != 13)
      png_chunk_error(png_ptr, "invalid");

   png_ptr->mode |= PNG_HAVE_IHDR;

   png_crc_read(png_ptr, buf, 13);
   png_crc_finish(png_ptr, 0);

   width = png_get_uint_31(png_ptr, buf);
   height = png_get_uint_31(png_ptr, buf + 4);
   bit_depth = buf[8];
   color_type = buf[9];
   compression_type = buf[10];
   filter_type = buf[11];
   interlace_type = buf[12];

   /* Set internal variables */
   png_ptr->width = width;
   png_ptr->height = height;
   png_ptr->bit_depth = (png_byte)bit_depth;
   png_ptr->interlaced = (png_byte)interlace_type;
   png_ptr->color_type = (png_byte)color_type;
#ifdef PNG_MNG_FEATURES_SUPPORTED
   png_ptr->filter_type = (png_byte)filter_type;
#endif
   png_ptr->compression_type = (png_byte)compression_type;

   /* Find number of channels */
   switch (png_ptr->color_type)
   {
      default: /* invalid, png_set_IHDR calls png_error */
      case PNG_COLOR_TYPE_GRAY:
      case PNG_COLOR_TYPE_PALETTE:
         png_ptr->channels = 1;
         break;

      case PNG_COLOR_TYPE_RGB:
         png_ptr->channels = 3;
         break;

      case PNG_COLOR_TYPE_GRAY_ALPHA:
         png_ptr->channels = 2;
         break;

      case PNG_COLOR_TYPE_RGB_ALPHA:
         png_ptr->channels = 4;
         break;
   }

   /* Set up other useful info */
   png_ptr->pixel_depth = (png_byte)(png_ptr->bit_depth * png_ptr->channels);
   png_ptr->rowbytes = PNG_ROWBYTES(png_ptr->pixel_depth, png_ptr->width);
   png_debug1(3, "bit_depth = %d", png_ptr->bit_depth);
   png_debug1(3, "channels = %d", png_ptr->channels);
   png_debug1(3, "rowbytes = %lu", (unsigned long)png_ptr->rowbytes);
   png_set_IHDR(png_ptr, info_ptr, width, height, bit_depth,
       color_type, interlace_type, compression_type, filter_type);
}