#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct texture_image {int member_3; unsigned int width; unsigned int height; int /*<<< orphan*/  supports_rgba; scalar_t__ pixels; int /*<<< orphan*/ * member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {scalar_t__ width; scalar_t__ height; int /*<<< orphan*/  supports_rgba; scalar_t__ pixels; } ;
struct nbio_image_handle {int status; int (* cb ) (TYPE_2__*,size_t) ;scalar_t__ upscale_threshold; TYPE_3__ ti; scalar_t__ is_finished; int /*<<< orphan*/  handle; int /*<<< orphan*/  type; scalar_t__ frame_duration; int /*<<< orphan*/  is_blocking; int /*<<< orphan*/  is_blocking_on_processing; } ;
typedef  scalar_t__ retro_time_t ;
struct TYPE_9__ {scalar_t__ state; } ;
typedef  TYPE_1__ retro_task_t ;
struct TYPE_10__ {scalar_t__ is_finished; scalar_t__ data; } ;
typedef  TYPE_2__ nbio_handle_t ;

/* Variables and functions */
#define  IMAGE_STATUS_PROCESS_TRANSFER 132 
#define  IMAGE_STATUS_PROCESS_TRANSFER_PARSE 131 
#define  IMAGE_STATUS_TRANSFER 130 
#define  IMAGE_STATUS_TRANSFER_PARSE 129 
#define  IMAGE_STATUS_WAIT 128 
 scalar_t__ cpu_features_get_time_usec () ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  image_transfer_iterate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int stub1 (TYPE_2__*,size_t) ; 
 int stub2 (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/  task_get_cancelled (TYPE_1__*) ; 
 int task_image_iterate_process_transfer (struct nbio_image_handle*) ; 
 int /*<<< orphan*/  task_set_data (TYPE_1__*,struct texture_image*) ; 
 scalar_t__ upscale_image (unsigned int,TYPE_3__*,struct texture_image*) ; 

bool task_image_load_handler(retro_task_t *task)
{
   nbio_handle_t            *nbio  = (nbio_handle_t*)task->state;
   struct nbio_image_handle *image = (struct nbio_image_handle*)nbio->data;

   if (image)
   {
      switch (image->status)
      {
         case IMAGE_STATUS_WAIT:
            return true;
         case IMAGE_STATUS_PROCESS_TRANSFER:
            if (task_image_iterate_process_transfer(image) == -1)
               image->status = IMAGE_STATUS_PROCESS_TRANSFER_PARSE;
            break;
         case IMAGE_STATUS_TRANSFER_PARSE:
            if (image->handle && image->cb)
            {
               size_t len = 0;
               if (image->cb(nbio, len) == -1)
                  return false;
            }
            if (image->is_blocking_on_processing)
               image->status = IMAGE_STATUS_PROCESS_TRANSFER;
            break;
         case IMAGE_STATUS_TRANSFER:
            if (!image->is_blocking && !image->is_finished)
            {
               retro_time_t start_time = cpu_features_get_time_usec();
               do
               {
                  if (!image_transfer_iterate(image->handle, image->type))
                  {
                     image->status = IMAGE_STATUS_TRANSFER_PARSE;
                     break;
                  }
               }
               while (cpu_features_get_time_usec() - start_time < image->frame_duration);
            }
            break;
         case IMAGE_STATUS_PROCESS_TRANSFER_PARSE:
            if (image->handle && image->cb)
            {
               size_t len = 0;
               if (image->cb(nbio, len) == -1)
                  return false;
            }
            if (!image->is_finished)
               break;
      }
   }

   if (     nbio->is_finished
         && (image && image->is_finished)
         && (!task_get_cancelled(task)))
   {
      struct texture_image *img = (struct texture_image*)malloc(sizeof(struct texture_image));

      if (img)
      {
         /* Upscale image, if required */
         if (image->upscale_threshold > 0)
         {
            if (((image->ti.width > 0) && (image->ti.height > 0)) &&
                ((image->ti.width  < image->upscale_threshold) ||
                 (image->ti.height < image->upscale_threshold)))
            {
               unsigned min_size                  = (image->ti.width < image->ti.height) ?
                                                      image->ti.width : image->ti.height;
               float scale_factor                 = (float)image->upscale_threshold /
                                                      (float)min_size;
               unsigned scale_factor_int          = (unsigned)scale_factor;
               struct texture_image img_resampled = {
                  0,
                  0,
                  NULL,
                  false
               };

               if (scale_factor - (float)scale_factor_int > 0.0f)
                  scale_factor_int += 1;

               if (upscale_image(scale_factor_int, &image->ti, &img_resampled))
               {
                  image->ti.width  = img_resampled.width;
                  image->ti.height = img_resampled.height;

                  if (image->ti.pixels)
                     free(image->ti.pixels);
                  image->ti.pixels = img_resampled.pixels;
               }
            }
         }

         img->width         = image->ti.width;
         img->height        = image->ti.height;
         img->pixels        = image->ti.pixels;
         img->supports_rgba = image->ti.supports_rgba;
      }

      task_set_data(task, img);

      return false;
   }

   return true;
}