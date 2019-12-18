#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  status; } ;
struct TYPE_11__ {scalar_t__ cmd; scalar_t__ data; } ;
struct TYPE_10__ {int /*<<< orphan*/  name; scalar_t__ userdata; } ;
typedef  int /*<<< orphan*/  MMAL_STATUS_T ;
typedef  TYPE_1__ MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_BUFFER_HEADER_T ;
typedef  TYPE_3__ MMALPLAY_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_INFO (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  LOG_TRACE (char*,int /*<<< orphan*/ ,TYPE_1__*,TYPE_2__*,char*) ; 
 scalar_t__ MMAL_EVENT_EOS ; 
 scalar_t__ MMAL_EVENT_ERROR ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_2__*) ; 
 int /*<<< orphan*/  mmal_status_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmalplay_stop (TYPE_3__*) ; 

__attribute__((used)) static void mmalplay_bh_control_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   MMALPLAY_T *ctx = (MMALPLAY_T *)port->userdata;
   LOG_TRACE("%s(%p),%p,%4.4s", port->name, port, buffer, (char *)&buffer->cmd);

   if (buffer->cmd == MMAL_EVENT_ERROR || buffer->cmd == MMAL_EVENT_EOS)
   {
      if (buffer->cmd == MMAL_EVENT_ERROR)
      {
         LOG_INFO("error event from %s: %s", port->name,
                  mmal_status_to_string(*(MMAL_STATUS_T*)buffer->data));
         ctx->status = *(MMAL_STATUS_T *)buffer->data;
      }
      else if (buffer->cmd == MMAL_EVENT_EOS)
         LOG_INFO("%s: EOS received", port->name);
      mmalplay_stop(ctx);
   }

   mmal_buffer_header_release(buffer);
}