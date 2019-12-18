#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* png_structrp ;
struct TYPE_13__ {scalar_t__ pixel_depth; scalar_t__ rowbytes; int /*<<< orphan*/  width; int /*<<< orphan*/  channels; int /*<<< orphan*/  bit_depth; int /*<<< orphan*/  color_type; } ;
typedef  TYPE_2__ png_row_info ;
struct TYPE_12__ {scalar_t__ pixel_depth; int transformations; scalar_t__ transformed_pixel_depth; scalar_t__ maximum_pixel_depth; scalar_t__ interlaced; int pass; int height; int /*<<< orphan*/ * row_buf; scalar_t__ prev_row; int /*<<< orphan*/  channels; int /*<<< orphan*/  bit_depth; int /*<<< orphan*/  color_type; int /*<<< orphan*/  iwidth; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNG_FILTER_VALUE_LAST ; 
 int /*<<< orphan*/  PNG_FILTER_VALUE_NONE ; 
 int PNG_INTERLACE ; 
 scalar_t__ PNG_ROWBYTES (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  png_do_read_interlace (TYPE_2__*,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  png_do_read_transformations (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  png_error (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  png_push_have_row (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  png_read_filter_row (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  png_read_push_finish_row (TYPE_1__*) ; 

void /* PRIVATE */
png_push_process_row(png_structrp png_ptr)
{
   /* 1.5.6: row_info moved out of png_struct to a local here. */
   png_row_info row_info;

   row_info.width = png_ptr->iwidth; /* NOTE: width of current interlaced row */
   row_info.color_type = png_ptr->color_type;
   row_info.bit_depth = png_ptr->bit_depth;
   row_info.channels = png_ptr->channels;
   row_info.pixel_depth = png_ptr->pixel_depth;
   row_info.rowbytes = PNG_ROWBYTES(row_info.pixel_depth, row_info.width);

   if (png_ptr->row_buf[0] > PNG_FILTER_VALUE_NONE)
   {
      if (png_ptr->row_buf[0] < PNG_FILTER_VALUE_LAST)
         png_read_filter_row(png_ptr, &row_info, png_ptr->row_buf + 1,
            png_ptr->prev_row + 1, png_ptr->row_buf[0]);
      else
         png_error(png_ptr, "bad adaptive filter value");
   }

   /* libpng 1.5.6: the following line was copying png_ptr->rowbytes before
    * 1.5.6, while the buffer really is this big in current versions of libpng
    * it may not be in the future, so this was changed just to copy the
    * interlaced row count:
    */
   memcpy(png_ptr->prev_row, png_ptr->row_buf, row_info.rowbytes + 1);

#ifdef PNG_READ_TRANSFORMS_SUPPORTED
   if (png_ptr->transformations != 0)
      png_do_read_transformations(png_ptr, &row_info);
#endif

   /* The transformed pixel depth should match the depth now in row_info. */
   if (png_ptr->transformed_pixel_depth == 0)
   {
      png_ptr->transformed_pixel_depth = row_info.pixel_depth;
      if (row_info.pixel_depth > png_ptr->maximum_pixel_depth)
         png_error(png_ptr, "progressive row overflow");
   }

   else if (png_ptr->transformed_pixel_depth != row_info.pixel_depth)
      png_error(png_ptr, "internal progressive row size calculation error");


#ifdef PNG_READ_INTERLACING_SUPPORTED
   /* Expand interlaced rows to full size */
   if (png_ptr->interlaced != 0 &&
       (png_ptr->transformations & PNG_INTERLACE) != 0)
   {
      if (png_ptr->pass < 6)
         png_do_read_interlace(&row_info, png_ptr->row_buf + 1, png_ptr->pass,
             png_ptr->transformations);

      switch (png_ptr->pass)
      {
         case 0:
         {
            int i;
            for (i = 0; i < 8 && png_ptr->pass == 0; i++)
            {
               png_push_have_row(png_ptr, png_ptr->row_buf + 1);
               png_read_push_finish_row(png_ptr); /* Updates png_ptr->pass */
            }

            if (png_ptr->pass == 2) /* Pass 1 might be empty */
            {
               for (i = 0; i < 4 && png_ptr->pass == 2; i++)
               {
                  png_push_have_row(png_ptr, NULL);
                  png_read_push_finish_row(png_ptr);
               }
            }

            if (png_ptr->pass == 4 && png_ptr->height <= 4)
            {
               for (i = 0; i < 2 && png_ptr->pass == 4; i++)
               {
                  png_push_have_row(png_ptr, NULL);
                  png_read_push_finish_row(png_ptr);
               }
            }

            if (png_ptr->pass == 6 && png_ptr->height <= 4)
            {
                png_push_have_row(png_ptr, NULL);
                png_read_push_finish_row(png_ptr);
            }

            break;
         }

         case 1:
         {
            int i;
            for (i = 0; i < 8 && png_ptr->pass == 1; i++)
            {
               png_push_have_row(png_ptr, png_ptr->row_buf + 1);
               png_read_push_finish_row(png_ptr);
            }

            if (png_ptr->pass == 2) /* Skip top 4 generated rows */
            {
               for (i = 0; i < 4 && png_ptr->pass == 2; i++)
               {
                  png_push_have_row(png_ptr, NULL);
                  png_read_push_finish_row(png_ptr);
               }
            }

            break;
         }

         case 2:
         {
            int i;

            for (i = 0; i < 4 && png_ptr->pass == 2; i++)
            {
               png_push_have_row(png_ptr, png_ptr->row_buf + 1);
               png_read_push_finish_row(png_ptr);
            }

            for (i = 0; i < 4 && png_ptr->pass == 2; i++)
            {
               png_push_have_row(png_ptr, NULL);
               png_read_push_finish_row(png_ptr);
            }

            if (png_ptr->pass == 4) /* Pass 3 might be empty */
            {
               for (i = 0; i < 2 && png_ptr->pass == 4; i++)
               {
                  png_push_have_row(png_ptr, NULL);
                  png_read_push_finish_row(png_ptr);
               }
            }

            break;
         }

         case 3:
         {
            int i;

            for (i = 0; i < 4 && png_ptr->pass == 3; i++)
            {
               png_push_have_row(png_ptr, png_ptr->row_buf + 1);
               png_read_push_finish_row(png_ptr);
            }

            if (png_ptr->pass == 4) /* Skip top two generated rows */
            {
               for (i = 0; i < 2 && png_ptr->pass == 4; i++)
               {
                  png_push_have_row(png_ptr, NULL);
                  png_read_push_finish_row(png_ptr);
               }
            }

            break;
         }

         case 4:
         {
            int i;

            for (i = 0; i < 2 && png_ptr->pass == 4; i++)
            {
               png_push_have_row(png_ptr, png_ptr->row_buf + 1);
               png_read_push_finish_row(png_ptr);
            }

            for (i = 0; i < 2 && png_ptr->pass == 4; i++)
            {
               png_push_have_row(png_ptr, NULL);
               png_read_push_finish_row(png_ptr);
            }

            if (png_ptr->pass == 6) /* Pass 5 might be empty */
            {
               png_push_have_row(png_ptr, NULL);
               png_read_push_finish_row(png_ptr);
            }

            break;
         }

         case 5:
         {
            int i;

            for (i = 0; i < 2 && png_ptr->pass == 5; i++)
            {
               png_push_have_row(png_ptr, png_ptr->row_buf + 1);
               png_read_push_finish_row(png_ptr);
            }

            if (png_ptr->pass == 6) /* Skip top generated row */
            {
               png_push_have_row(png_ptr, NULL);
               png_read_push_finish_row(png_ptr);
            }

            break;
         }

         default:
         case 6:
         {
            png_push_have_row(png_ptr, png_ptr->row_buf + 1);
            png_read_push_finish_row(png_ptr);

            if (png_ptr->pass != 6)
               break;

            png_push_have_row(png_ptr, NULL);
            png_read_push_finish_row(png_ptr);
         }
      }
   }
   else
#endif
   {
      png_push_have_row(png_ptr, png_ptr->row_buf + 1);
      png_read_push_finish_row(png_ptr);
   }
}