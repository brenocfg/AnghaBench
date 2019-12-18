#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ cmd; int length; scalar_t__ data; } ;
struct TYPE_9__ {scalar_t__ size; int id; } ;
struct TYPE_12__ {TYPE_1__ hdr; } ;
struct TYPE_11__ {int /*<<< orphan*/  status; } ;
struct TYPE_10__ {int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  MMAL_PORT_T ;
typedef  TYPE_2__ MMAL_PARAMETER_UINT32_T ;
typedef  TYPE_3__ MMAL_PARAMETER_FOCUS_STATUS_T ;
typedef  TYPE_4__ MMAL_EVENT_PARAMETER_CHANGED_T ;
typedef  TYPE_5__ MMAL_BUFFER_HEADER_T ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (char*,int /*<<< orphan*/ *,TYPE_5__*,scalar_t__) ; 
 int /*<<< orphan*/  LOG_ERROR (char*,scalar_t__) ; 
 int /*<<< orphan*/  LOG_INFO (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MMAL_CAM_AUTOFOCUS_COMPLETE ; 
 scalar_t__ MMAL_EVENT_PARAMETER_CHANGED ; 
#define  MMAL_PARAMETER_CAMERA_NUM 129 
#define  MMAL_PARAMETER_FOCUS_STATUS 128 
 int /*<<< orphan*/  VCOS_OR ; 
 int /*<<< orphan*/  events ; 
 int /*<<< orphan*/  mmal_buffer_header_release (TYPE_5__*) ; 
 int /*<<< orphan*/  vcos_assert (int) ; 
 int /*<<< orphan*/  vcos_event_flags_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void control_bh_cb(MMAL_PORT_T *port, MMAL_BUFFER_HEADER_T *buffer)
{
   LOG_DEBUG("control_bh_cb %p,%p (cmd=0x%08x)", port, buffer, buffer->cmd);
   if (buffer->cmd == MMAL_EVENT_PARAMETER_CHANGED)
   {
      MMAL_EVENT_PARAMETER_CHANGED_T *param = (MMAL_EVENT_PARAMETER_CHANGED_T *)buffer->data;

      vcos_assert(buffer->length >= sizeof(MMAL_EVENT_PARAMETER_CHANGED_T));
      vcos_assert(buffer->length == param->hdr.size);
      switch (param->hdr.id)
      {
         case MMAL_PARAMETER_FOCUS_STATUS:
            vcos_assert(param->hdr.size == sizeof(MMAL_PARAMETER_FOCUS_STATUS_T));
            {
               MMAL_PARAMETER_FOCUS_STATUS_T *focus_status = (MMAL_PARAMETER_FOCUS_STATUS_T *)param;
               LOG_INFO("Focus status: %d", focus_status->status);
               vcos_event_flags_set(&events, MMAL_CAM_AUTOFOCUS_COMPLETE, VCOS_OR);
            }
            break;
         case MMAL_PARAMETER_CAMERA_NUM:
            vcos_assert(param->hdr.size == sizeof(MMAL_PARAMETER_UINT32_T));
            {
               MMAL_PARAMETER_UINT32_T *camera_num = (MMAL_PARAMETER_UINT32_T *)param;
               LOG_INFO("Camera number: %d", camera_num->value);
            }
            break;
         default:
            LOG_ERROR("Unexpected changed event for parameter 0x%08x", param->hdr.id);
      }
   }
   else
   {
      LOG_ERROR("Unexpected event, 0x%08x", buffer->cmd);
   }
   mmal_buffer_header_release(buffer);
}