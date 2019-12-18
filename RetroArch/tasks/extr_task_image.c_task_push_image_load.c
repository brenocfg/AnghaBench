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
struct TYPE_7__ {int supports_rgba; int /*<<< orphan*/ * pixels; scalar_t__ height; scalar_t__ width; } ;
struct nbio_image_handle {int is_blocking; int is_blocking_on_processing; int is_finished; unsigned int upscale_threshold; int /*<<< orphan*/  type; TYPE_1__ ti; int /*<<< orphan*/ * handle; scalar_t__ size; scalar_t__ frame_duration; scalar_t__ processing_final_state; int /*<<< orphan*/  status; } ;
struct TYPE_8__ {int is_finished; void* user_data; int /*<<< orphan*/  callback; int /*<<< orphan*/  cleanup; int /*<<< orphan*/  handler; struct TYPE_8__* state; struct nbio_image_handle* data; int /*<<< orphan*/  type; int /*<<< orphan*/  path; scalar_t__ status_flags; int /*<<< orphan*/ * cb; int /*<<< orphan*/ * msg_queue; int /*<<< orphan*/ * handle; scalar_t__ pos_increment; int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ retro_task_t ;
typedef  int /*<<< orphan*/  retro_task_callback_t ;
typedef  TYPE_2__ nbio_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  BIT32_SET (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IMAGE_STATUS_WAIT ; 
 int /*<<< orphan*/  IMAGE_TYPE_BMP ; 
 int /*<<< orphan*/  IMAGE_TYPE_JPEG ; 
 int /*<<< orphan*/  IMAGE_TYPE_NONE ; 
 int /*<<< orphan*/  IMAGE_TYPE_PNG ; 
 int /*<<< orphan*/  IMAGE_TYPE_TGA ; 
 int /*<<< orphan*/  NBIO_FLAG_IMAGE_SUPPORTS_RGBA ; 
 int /*<<< orphan*/  NBIO_STATUS_INIT ; 
 int /*<<< orphan*/  NBIO_TYPE_BMP ; 
 int /*<<< orphan*/  NBIO_TYPE_JPEG ; 
 int /*<<< orphan*/  NBIO_TYPE_NONE ; 
 int /*<<< orphan*/  NBIO_TYPE_PNG ; 
 int /*<<< orphan*/  NBIO_TYPE_TGA ; 
 int /*<<< orphan*/  cb_nbio_image_thumbnail ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strdup (char const*) ; 
 scalar_t__ strstr (char const*,char*) ; 
 int /*<<< orphan*/  task_file_load_handler ; 
 int /*<<< orphan*/  task_image_load_free ; 
 TYPE_2__* task_init () ; 
 int /*<<< orphan*/  task_queue_push (TYPE_2__*) ; 

bool task_push_image_load(const char *fullpath, 
      bool supports_rgba, unsigned upscale_threshold,
      retro_task_callback_t cb, void *user_data)
{
   nbio_handle_t             *nbio   = NULL;
   struct nbio_image_handle   *image = NULL;
   retro_task_t                   *t = task_init();

   if (!t)
      return false;

   nbio                = (nbio_handle_t*)malloc(sizeof(*nbio));

   if (!nbio)
   {
      free(t);
      return false;
   }

   nbio->type          = NBIO_TYPE_NONE;
   nbio->is_finished   = false;
   nbio->status        = NBIO_STATUS_INIT;
   nbio->pos_increment = 0;
   nbio->status_flags  = 0;
   nbio->data          = NULL;
   nbio->handle        = NULL;
   nbio->msg_queue     = NULL;
   nbio->cb            = &cb_nbio_image_thumbnail;

   if (supports_rgba)
      BIT32_SET(nbio->status_flags, NBIO_FLAG_IMAGE_SUPPORTS_RGBA);

   image              = (struct nbio_image_handle*)malloc(sizeof(*image));
   if (!image)
   {
      free(nbio);
      free(t);
      return false;
   }

   nbio->path                        = strdup(fullpath);

   image->type                       = IMAGE_TYPE_NONE;
   image->status                     = IMAGE_STATUS_WAIT;
   image->is_blocking                = false;
   image->is_blocking_on_processing  = false;
   image->is_finished                = false;
   image->processing_final_state     = 0;
   image->frame_duration             = 0;
   image->size                       = 0;
   image->upscale_threshold          = upscale_threshold;
   image->handle                     = NULL;

   image->ti.width                   = 0;
   image->ti.height                  = 0;
   image->ti.pixels                  = NULL;
   /* TODO/FIXME - shouldn't we set this ? */
   image->ti.supports_rgba           = false;

   if (strstr(fullpath, ".png"))
   {
      nbio->type       = NBIO_TYPE_PNG;
      image->type      = IMAGE_TYPE_PNG;
   }
   else if (strstr(fullpath, ".jpeg")
         || strstr(fullpath, ".jpg"))
   {
      nbio->type       = NBIO_TYPE_JPEG;
      image->type      = IMAGE_TYPE_JPEG;
   }
   else if (strstr(fullpath, ".bmp"))
   {
      nbio->type       = NBIO_TYPE_BMP;
      image->type      = IMAGE_TYPE_BMP;
   }
   else if (strstr(fullpath, ".tga"))
   {
      nbio->type       = NBIO_TYPE_TGA;
      image->type      = IMAGE_TYPE_TGA;
   }

   nbio->data          = (struct nbio_image_handle*)image;

   t->state           = nbio;
   t->handler         = task_file_load_handler;
   t->cleanup         = task_image_load_free;
   t->callback        = cb;
   t->user_data       = user_data;

   task_queue_push(t);

   return true;
}