#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_41__   TYPE_9__ ;
typedef  struct TYPE_40__   TYPE_8__ ;
typedef  struct TYPE_39__   TYPE_7__ ;
typedef  struct TYPE_38__   TYPE_6__ ;
typedef  struct TYPE_37__   TYPE_5__ ;
typedef  struct TYPE_36__   TYPE_4__ ;
typedef  struct TYPE_35__   TYPE_3__ ;
typedef  struct TYPE_34__   TYPE_2__ ;
typedef  struct TYPE_33__   TYPE_23__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_19__ ;
typedef  struct TYPE_30__   TYPE_13__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_41__ {TYPE_19__* format; int /*<<< orphan*/  component; TYPE_2__* priv; } ;
struct TYPE_40__ {unsigned int w; unsigned int h; scalar_t__ y; int /*<<< orphan*/  x; } ;
struct TYPE_39__ {unsigned int width; unsigned int height; scalar_t__ y; int /*<<< orphan*/  x; } ;
struct TYPE_37__ {unsigned int width; unsigned int height; } ;
struct TYPE_38__ {TYPE_5__ video; } ;
struct TYPE_35__ {int* offset; int /*<<< orphan*/ * pitch; } ;
struct TYPE_36__ {TYPE_3__ video; } ;
struct TYPE_34__ {scalar_t__ (* pf_set_format ) (TYPE_9__*) ;} ;
struct TYPE_33__ {int /*<<< orphan*/ * pitches; int /*<<< orphan*/ ** pixels; } ;
struct TYPE_32__ {TYPE_12__* module; } ;
struct TYPE_31__ {TYPE_6__* es; } ;
struct TYPE_30__ {int flags; scalar_t__ length; scalar_t__ offset; TYPE_4__* type; int /*<<< orphan*/ * data; scalar_t__ cmd; } ;
struct TYPE_29__ {scalar_t__ status; TYPE_23__* sdl_overlay; TYPE_7__ display_region; int /*<<< orphan*/  queue; } ;
struct TYPE_28__ {TYPE_1__* priv; TYPE_9__** input; } ;
struct TYPE_27__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_8__ SDL_Rect ;
typedef  TYPE_9__ MMAL_PORT_T ;
typedef  TYPE_10__ MMAL_EVENT_FORMAT_CHANGED_T ;
typedef  TYPE_11__ MMAL_COMPONENT_T ;
typedef  TYPE_12__ MMAL_COMPONENT_MODULE_T ;
typedef  TYPE_13__ MMAL_BUFFER_HEADER_T ;
typedef  int MMAL_BOOL_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_ERROR (char*,...) ; 
 int MMAL_BUFFER_HEADER_FLAG_EOS ; 
 scalar_t__ MMAL_SUCCESS ; 
 int /*<<< orphan*/  SDL_DisplayYUVOverlay (TYPE_23__*,TYPE_8__*) ; 
 int /*<<< orphan*/  SDL_LockYUVOverlay (TYPE_23__*) ; 
 int /*<<< orphan*/  SDL_UnlockYUVOverlay (TYPE_23__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  mmal_event_eos_send (TYPE_9__*) ; 
 scalar_t__ mmal_event_error_send (int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_10__* mmal_event_format_changed_get (TYPE_13__*) ; 
 int /*<<< orphan*/  mmal_format_copy (TYPE_19__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmal_port_buffer_header_callback (TYPE_9__*,TYPE_13__*) ; 
 TYPE_13__* mmal_queue_get (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_9__*) ; 

__attribute__((used)) static MMAL_BOOL_T sdl_do_processing(MMAL_COMPONENT_T *component)
{
   MMAL_PORT_T *port = component->input[0];
   MMAL_COMPONENT_MODULE_T *module = component->priv->module;
   unsigned int width = port->format->es->video.width;
   unsigned int height = port->format->es->video.height;
   MMAL_BUFFER_HEADER_T *buffer;
   uint8_t *src_plane[3];
   uint32_t *src_pitch;
   unsigned int i, line;
   MMAL_BOOL_T eos;
   SDL_Rect rect;

   buffer = mmal_queue_get(module->queue);
   if (!buffer)
	   return 0;

   eos = buffer->flags & MMAL_BUFFER_HEADER_FLAG_EOS;

   /* Handle event buffers */
   if (buffer->cmd)
   {
      MMAL_EVENT_FORMAT_CHANGED_T *event = mmal_event_format_changed_get(buffer);
      if (event)
      {
         mmal_format_copy(port->format, event->format);
         module->status = port->priv->pf_set_format(port);
         if (module->status != MMAL_SUCCESS)
         {
            LOG_ERROR("format not set on port %p", port);
            if (mmal_event_error_send(port->component, module->status) != MMAL_SUCCESS)
               LOG_ERROR("unable to send an error event buffer");
         }
      }
      else
      {
         LOG_ERROR("discarding event %i on port %p", (int)buffer->cmd, port);
      }

      buffer->length = 0;
      mmal_port_buffer_header_callback(port, buffer);
      return 1;
   }

   if (module->status != MMAL_SUCCESS)
      return 1;

   /* Ignore empty buffers */
   if (!buffer->length)
      goto end;

   // FIXME: sanity check the size of the buffer

   /* Blit the buffer onto the overlay. */
   src_pitch = buffer->type->video.pitch;
   src_plane[0] = buffer->data + buffer->type->video.offset[0];
   src_plane[1] = buffer->data + buffer->type->video.offset[2];
   src_plane[2] = buffer->data + buffer->type->video.offset[1];

   SDL_LockYUVOverlay(module->sdl_overlay);
   for (i=0; i<3; i++)
   {
      uint8_t *src = src_plane[i];
      uint8_t *dst = module->sdl_overlay->pixels[i];

      if(i == 1) {width /= 2; height /= 2;}
      for(line = 0; line < height; line++)
      {
         memcpy(dst, src, width);
         src += src_pitch[i];
         dst += module->sdl_overlay->pitches[i];
      }
   }
   SDL_UnlockYUVOverlay(module->sdl_overlay);

   width = port->format->es->video.width;
   height = port->format->es->video.height;
   rect.x = module->display_region.x;
   rect.w = module->display_region.width;
   height = rect.w * height / width;
   rect.y = module->display_region.y + (module->display_region.height - height) / 2;
   rect.h = height;

   SDL_DisplayYUVOverlay(module->sdl_overlay, &rect);

 end:
   buffer->offset = buffer->length = 0;
   mmal_port_buffer_header_callback(port, buffer);

   /* Generate EOS events */
   if (eos)
      mmal_event_eos_send(port);

   return 1;
}