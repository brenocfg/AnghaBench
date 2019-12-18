#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int length; int flags; int /*<<< orphan*/  data; } ;
struct TYPE_23__ {scalar_t__ is_enabled; TYPE_3__* format; scalar_t__ userdata; } ;
struct TYPE_22__ {int /*<<< orphan*/  complete_semaphore; TYPE_5__* pstate; scalar_t__ file_handle; } ;
struct TYPE_21__ {TYPE_4__* camera_pool; scalar_t__ onlyLuma; } ;
struct TYPE_20__ {int /*<<< orphan*/  queue; } ;
struct TYPE_19__ {TYPE_2__* es; } ;
struct TYPE_17__ {int width; int height; } ;
struct TYPE_18__ {TYPE_1__ video; } ;
typedef  TYPE_6__ PORT_USERDATA ;
typedef  scalar_t__ MMAL_STATUS_T ;
typedef  TYPE_7__ MMAL_PORT_T ;
typedef  TYPE_8__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int MMAL_BUFFER_HEADER_FLAG_FRAME_END ; 
 int MMAL_BUFFER_HEADER_FLAG_TRANSMISSION_FAILED ; 
 scalar_t__ MMAL_SUCCESS ; 
 int fwrite (int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  mmal_buffer_header_mem_lock (TYPE_8__*) ; 
 int /*<<< orphan*/  mmal_buffer_header_mem_unlock (TYPE_8__*) ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_8__*) ; 
 scalar_t__ mmal_port_send_buffer (TYPE_7__*,TYPE_8__*) ; 
 TYPE_8__* mmal_queue_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcos_log_error (char*,...) ; 
 int vcos_min (int,int) ; 
 int /*<<< orphan*/  vcos_semaphore_post (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void camera_buffer_callback(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   int complete = 0;
   // We pass our file handle and other stuff in via the userdata field.

   PORT_USERDATA *pData = (PORT_USERDATA *)port->userdata;

   if (pData)
   {
      int bytes_written = 0;
      int bytes_to_write = buffer->length;

      if (pData->pstate->onlyLuma)
         bytes_to_write = vcos_min(buffer->length, port->format->es->video.width * port->format->es->video.height);

      if (bytes_to_write && pData->file_handle)
      {
         mmal_buffer_header_mem_lock(buffer);

         bytes_written = fwrite(buffer->data, 1, bytes_to_write, pData->file_handle);

         mmal_buffer_header_mem_unlock(buffer);
      }

      // We need to check we wrote what we wanted - it's possible we have run out of storage.
      if (buffer->length && bytes_written != bytes_to_write)
      {
         vcos_log_error("Unable to write buffer to file - aborting %d vs %d", bytes_written, bytes_to_write);
         complete = 1;
      }

      // Check end of frame or error
      if (buffer->flags & (MMAL_BUFFER_HEADER_FLAG_FRAME_END | MMAL_BUFFER_HEADER_FLAG_TRANSMISSION_FAILED))
         complete = 1;
   }
   else
   {
      vcos_log_error("Received a camera still buffer callback with no state");
   }

   // release buffer back to the pool
   mmal_buffer_header_release(buffer);

   // and send one back to the port (if still open)
   if (port->is_enabled)
   {
      MMAL_STATUS_T status;
      MMAL_BUFFER_HEADER_T *new_buffer = mmal_queue_get(pData->pstate->camera_pool->queue);

      // and back to the port from there.
      if (new_buffer)
      {
         status = mmal_port_send_buffer(port, new_buffer);
      }

      if (!new_buffer || status != MMAL_SUCCESS)
         vcos_log_error("Unable to return the buffer to the camera still port");
   }

   if (complete)
   {
      vcos_semaphore_post(&(pData->complete_semaphore));
   }
}