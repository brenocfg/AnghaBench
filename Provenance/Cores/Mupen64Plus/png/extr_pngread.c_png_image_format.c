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
typedef  int /*<<< orphan*/  png_uint_32 ;
typedef  TYPE_1__* png_structrp ;
struct TYPE_3__ {int color_type; scalar_t__ num_trans; int bit_depth; } ;

/* Variables and functions */
 int PNG_COLOR_MASK_ALPHA ; 
 int PNG_COLOR_MASK_COLOR ; 
 int PNG_COLOR_MASK_PALETTE ; 
 int /*<<< orphan*/  PNG_FORMAT_FLAG_ALPHA ; 
 int /*<<< orphan*/  PNG_FORMAT_FLAG_COLOR ; 
 int /*<<< orphan*/  PNG_FORMAT_FLAG_COLORMAP ; 
 int /*<<< orphan*/  PNG_FORMAT_FLAG_LINEAR ; 

__attribute__((used)) static png_uint_32
png_image_format(png_structrp png_ptr)
{
   png_uint_32 format = 0;

   if ((png_ptr->color_type & PNG_COLOR_MASK_COLOR) != 0)
      format |= PNG_FORMAT_FLAG_COLOR;

   if ((png_ptr->color_type & PNG_COLOR_MASK_ALPHA) != 0)
      format |= PNG_FORMAT_FLAG_ALPHA;

   /* Use png_ptr here, not info_ptr, because by examination png_handle_tRNS
    * sets the png_struct fields; that's all we are interested in here.  The
    * precise interaction with an app call to png_set_tRNS and PNG file reading
    * is unclear.
    */
   else if (png_ptr->num_trans > 0)
      format |= PNG_FORMAT_FLAG_ALPHA;

   if (png_ptr->bit_depth == 16)
      format |= PNG_FORMAT_FLAG_LINEAR;

   if ((png_ptr->color_type & PNG_COLOR_MASK_PALETTE) != 0)
      format |= PNG_FORMAT_FLAG_COLORMAP;

   return format;
}