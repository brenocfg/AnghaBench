#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_28__ {scalar_t__ is_enabled; TYPE_3__* format; scalar_t__ userdata; } ;
struct TYPE_27__ {int abort; scalar_t__ lasttime; int starttime; TYPE_7__* pstate; int /*<<< orphan*/  frame; scalar_t__ pts_file_handle; int /*<<< orphan*/  file_handle; } ;
struct TYPE_24__ {int enable_annotate; char* annotate_string; int /*<<< orphan*/  annotate_y; int /*<<< orphan*/  annotate_x; int /*<<< orphan*/  annotate_justify; int /*<<< orphan*/  annotate_bg_colour; int /*<<< orphan*/  annotate_text_colour; int /*<<< orphan*/  annotate_text_size; } ;
struct TYPE_23__ {scalar_t__ gps; } ;
struct TYPE_26__ {scalar_t__ frame; scalar_t__ starttime; TYPE_6__* camera_pool; TYPE_5__ camera_parameters; int /*<<< orphan*/  camera_component; TYPE_4__ common_settings; scalar_t__ onlyLuma; } ;
struct TYPE_25__ {int /*<<< orphan*/  queue; } ;
struct TYPE_22__ {TYPE_2__* es; } ;
struct TYPE_20__ {int width; int height; } ;
struct TYPE_21__ {TYPE_1__ video; } ;
struct TYPE_19__ {int length; scalar_t__ pts; int /*<<< orphan*/  data; } ;
typedef  TYPE_7__ RASPIVIDYUV_STATE ;
typedef  TYPE_8__ PORT_USERDATA ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_9__ MMAL_PORT_T ;
typedef  TYPE_10__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int ANNOTATE_APP_TEXT ; 
 scalar_t__ MMAL_SUCCESS ; 
 scalar_t__ MMAL_TIME_UNKNOWN ; 
 int /*<<< orphan*/  fprintf (scalar_t__,char*,int,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int fwrite (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int get_microseconds64 () ; 
 int /*<<< orphan*/  mmal_buffer_header_mem_lock (TYPE_10__*) ; 
 int /*<<< orphan*/  mmal_buffer_header_mem_unlock (TYPE_10__*) ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_10__*) ; 
 scalar_t__ mmal_port_send_buffer (TYPE_9__*,TYPE_10__*) ; 
 TYPE_10__* mmal_queue_get (int /*<<< orphan*/ ) ; 
 char* raspi_gps_location_string () ; 
 int /*<<< orphan*/  raspicamcontrol_set_annotate (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_error (char*,...) ; 
 int vcos_min (int,int) ; 

__attribute__((used)) static void camera_buffer_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   MMAL_BUFFER_HEADER_T *new_buffer;
   static int64_t last_second = -1;

   // We pass our file handle and other stuff in via the userdata field.

   PORT_USERDATA *pData = (PORT_USERDATA *)port->userdata;
   RASPIVIDYUV_STATE *pstate = pData->pstate;

   if (pData)
   {
      int bytes_written = 0;
      int bytes_to_write = buffer->length;
      int64_t current_time = get_microseconds64()/1000000;

      if (pstate->onlyLuma)
         bytes_to_write = vcos_min(buffer->length, port->format->es->video.width * port->format->es->video.height);

      vcos_assert(pData->file_handle);

      if (bytes_to_write)
      {
         mmal_buffer_header_mem_lock(buffer);
         bytes_written = fwrite(buffer->data, 1, bytes_to_write, pData->file_handle);
         mmal_buffer_header_mem_unlock(buffer);

         if (bytes_written != bytes_to_write)
         {
            vcos_log_error("Failed to write buffer data (%d from %d)- aborting", bytes_written, bytes_to_write);
            pData->abort = 1;
         }
         if (pData->pts_file_handle)
         {
            // Every buffer should be a complete frame, so no need to worry about
            // fragments or duplicated timestamps. We're also in RESET_STC mode, so
            // the time on frame 0 should always be 0 anyway, but simply copy the
            // code from raspivid.
            // MMAL_TIME_UNKNOWN should never happen, but it'll corrupt the timestamps
            // file if saved.
            if(buffer->pts != MMAL_TIME_UNKNOWN)
            {
               int64_t pts;
               if(pstate->frame==0)
                  pstate->starttime=buffer->pts;
               pData->lasttime=buffer->pts;
               pts = buffer->pts - pData->starttime;
               fprintf(pData->pts_file_handle,"%lld.%03lld\n", pts/1000, pts%1000);
               pData->frame++;
            }
         }
      }

      // See if the second count has changed and we need to update any annotation
      if (current_time != last_second)
      {
         if ((pstate->camera_parameters.enable_annotate & ANNOTATE_APP_TEXT) && pstate->common_settings.gps)
         {
            char *text = raspi_gps_location_string();
            raspicamcontrol_set_annotate(pstate->camera_component, pstate->camera_parameters.enable_annotate,
                                         text,
                                         pstate->camera_parameters.annotate_text_size,
                                         pstate->camera_parameters.annotate_text_colour,
                                         pstate->camera_parameters.annotate_bg_colour,
                                         pstate->camera_parameters.annotate_justify,
                                         pstate->camera_parameters.annotate_x,
                                         pstate->camera_parameters.annotate_y
                                        );
            free(text);
         }
         else
            raspicamcontrol_set_annotate(pstate->camera_component, pstate->camera_parameters.enable_annotate,
                                         pstate->camera_parameters.annotate_string,
                                         pstate->camera_parameters.annotate_text_size,
                                         pstate->camera_parameters.annotate_text_colour,
                                         pstate->camera_parameters.annotate_bg_colour,
                                         pstate->camera_parameters.annotate_justify,
                                         pstate->camera_parameters.annotate_x,
                                         pstate->camera_parameters.annotate_y
                                        );
         last_second = current_time;
      }

   }
   else
   {
      vcos_log_error("Received a camera buffer callback with no state");
   }

   // release buffer back to the pool
   mmal_buffer_header_release(buffer);

   // and send one back to the port (if still open)
   if (port->is_enabled)
   {
      MMAL_STATUS_T status;

      new_buffer = mmal_queue_get(pData->pstate->camera_pool->queue);

      if (new_buffer)
         status = mmal_port_send_buffer(port, new_buffer);

      if (!new_buffer || status != MMAL_SUCCESS)
         vcos_log_error("Unable to return a buffer to the camera port");
   }
}