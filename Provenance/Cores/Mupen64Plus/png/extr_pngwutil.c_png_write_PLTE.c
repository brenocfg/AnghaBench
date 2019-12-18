#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ png_uint_32 ;
typedef  scalar_t__ png_uint_16 ;
typedef  TYPE_1__* png_structrp ;
typedef  int /*<<< orphan*/  png_size_t ;
typedef  TYPE_2__* png_const_colorp ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_11__ {int /*<<< orphan*/  blue; int /*<<< orphan*/  green; int /*<<< orphan*/  red; } ;
struct TYPE_10__ {int color_type; int bit_depth; int mng_features_permitted; int /*<<< orphan*/  mode; scalar_t__ num_palette; } ;

/* Variables and functions */
 int PNG_COLOR_MASK_COLOR ; 
 int PNG_COLOR_TYPE_PALETTE ; 
 int PNG_FLAG_MNG_EMPTY_PLTE ; 
 int /*<<< orphan*/  PNG_HAVE_PLTE ; 
 int PNG_MAX_PALETTE_LENGTH ; 
 int /*<<< orphan*/  png_PLTE ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 int /*<<< orphan*/  png_debug1 (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_warning (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_write_chunk_data (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_write_chunk_end (TYPE_1__*) ; 
 int /*<<< orphan*/  png_write_chunk_header (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 

void /* PRIVATE */
png_write_PLTE(png_structrp png_ptr, png_const_colorp palette,
    png_uint_32 num_pal)
{
   png_uint_32 max_palette_length, i;
   png_const_colorp pal_ptr;
   png_byte buf[3];

   png_debug(1, "in png_write_PLTE");

   max_palette_length = (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE) ?
      (1 << png_ptr->bit_depth) : PNG_MAX_PALETTE_LENGTH;

   if ((
#ifdef PNG_MNG_FEATURES_SUPPORTED
       (png_ptr->mng_features_permitted & PNG_FLAG_MNG_EMPTY_PLTE) == 0 &&
#endif
       num_pal == 0) || num_pal > max_palette_length)
   {
      if (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE)
      {
         png_error(png_ptr, "Invalid number of colors in palette");
      }

      else
      {
         png_warning(png_ptr, "Invalid number of colors in palette");
         return;
      }
   }

   if ((png_ptr->color_type & PNG_COLOR_MASK_COLOR) == 0)
   {
      png_warning(png_ptr,
          "Ignoring request to write a PLTE chunk in grayscale PNG");

      return;
   }

   png_ptr->num_palette = (png_uint_16)num_pal;
   png_debug1(3, "num_palette = %d", png_ptr->num_palette);

   png_write_chunk_header(png_ptr, png_PLTE, (png_uint_32)(num_pal * 3));
#ifdef PNG_POINTER_INDEXING_SUPPORTED

   for (i = 0, pal_ptr = palette; i < num_pal; i++, pal_ptr++)
   {
      buf[0] = pal_ptr->red;
      buf[1] = pal_ptr->green;
      buf[2] = pal_ptr->blue;
      png_write_chunk_data(png_ptr, buf, (png_size_t)3);
   }

#else
   /* This is a little slower but some buggy compilers need to do this
    * instead
    */
   pal_ptr=palette;

   for (i = 0; i < num_pal; i++)
   {
      buf[0] = pal_ptr[i].red;
      buf[1] = pal_ptr[i].green;
      buf[2] = pal_ptr[i].blue;
      png_write_chunk_data(png_ptr, buf, (png_size_t)3);
   }

#endif
   png_write_chunk_end(png_ptr);
   png_ptr->mode |= PNG_HAVE_PLTE;
}