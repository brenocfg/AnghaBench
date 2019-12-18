#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int png_uint_32 ;
typedef  int png_uint_16 ;
typedef  TYPE_1__* png_structrp ;
typedef  TYPE_2__* png_inforp ;
typedef  int /*<<< orphan*/  png_byte ;
struct TYPE_14__ {void* blue; void* green; void* red; void* gray; } ;
struct TYPE_13__ {int valid; } ;
struct TYPE_12__ {int mode; scalar_t__ color_type; int num_trans; TYPE_5__ trans_color; scalar_t__ num_palette; } ;

/* Variables and functions */
 scalar_t__ PNG_COLOR_TYPE_GRAY ; 
 scalar_t__ PNG_COLOR_TYPE_PALETTE ; 
 scalar_t__ PNG_COLOR_TYPE_RGB ; 
 int PNG_HAVE_IDAT ; 
 int PNG_HAVE_IHDR ; 
 int PNG_HAVE_PLTE ; 
 int PNG_INFO_tRNS ; 
 int PNG_MAX_PALETTE_LENGTH ; 
 int /*<<< orphan*/  png_chunk_benign_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_chunk_error (TYPE_1__*,char*) ; 
 scalar_t__ png_crc_finish (TYPE_1__*,int) ; 
 int /*<<< orphan*/  png_crc_read (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  png_debug (int,char*) ; 
 void* png_get_uint_16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_set_tRNS (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,int,TYPE_5__*) ; 

void /* PRIVATE */
png_handle_tRNS(png_structrp png_ptr, png_inforp info_ptr, png_uint_32 length)
{
   png_byte readbuf[PNG_MAX_PALETTE_LENGTH];

   png_debug(1, "in png_handle_tRNS");

   if ((png_ptr->mode & PNG_HAVE_IHDR) == 0)
      png_chunk_error(png_ptr, "missing IHDR");

   else if ((png_ptr->mode & PNG_HAVE_IDAT) != 0)
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "out of place");
      return;
   }

   else if (info_ptr != NULL && (info_ptr->valid & PNG_INFO_tRNS) != 0)
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "duplicate");
      return;
   }

   if (png_ptr->color_type == PNG_COLOR_TYPE_GRAY)
   {
      png_byte buf[2];

      if (length != 2)
      {
         png_crc_finish(png_ptr, length);
         png_chunk_benign_error(png_ptr, "invalid");
         return;
      }

      png_crc_read(png_ptr, buf, 2);
      png_ptr->num_trans = 1;
      png_ptr->trans_color.gray = png_get_uint_16(buf);
   }

   else if (png_ptr->color_type == PNG_COLOR_TYPE_RGB)
   {
      png_byte buf[6];

      if (length != 6)
      {
         png_crc_finish(png_ptr, length);
         png_chunk_benign_error(png_ptr, "invalid");
         return;
      }

      png_crc_read(png_ptr, buf, length);
      png_ptr->num_trans = 1;
      png_ptr->trans_color.red = png_get_uint_16(buf);
      png_ptr->trans_color.green = png_get_uint_16(buf + 2);
      png_ptr->trans_color.blue = png_get_uint_16(buf + 4);
   }

   else if (png_ptr->color_type == PNG_COLOR_TYPE_PALETTE)
   {
      if ((png_ptr->mode & PNG_HAVE_PLTE) == 0)
      {
         /* TODO: is this actually an error in the ISO spec? */
         png_crc_finish(png_ptr, length);
         png_chunk_benign_error(png_ptr, "out of place");
         return;
      }

      if (length > (unsigned int) png_ptr->num_palette ||
         length > (unsigned int) PNG_MAX_PALETTE_LENGTH ||
         length == 0)
      {
         png_crc_finish(png_ptr, length);
         png_chunk_benign_error(png_ptr, "invalid");
         return;
      }

      png_crc_read(png_ptr, readbuf, length);
      png_ptr->num_trans = (png_uint_16)length;
   }

   else
   {
      png_crc_finish(png_ptr, length);
      png_chunk_benign_error(png_ptr, "invalid with alpha channel");
      return;
   }

   if (png_crc_finish(png_ptr, 0) != 0)
   {
      png_ptr->num_trans = 0;
      return;
   }

   /* TODO: this is a horrible side effect in the palette case because the
    * png_struct ends up with a pointer to the tRNS buffer owned by the
    * png_info.  Fix this.
    */
   png_set_tRNS(png_ptr, info_ptr, readbuf, png_ptr->num_trans,
       &(png_ptr->trans_color));
}