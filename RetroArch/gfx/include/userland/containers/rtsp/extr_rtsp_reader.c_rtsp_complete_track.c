#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_6__ ;
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_2__* priv; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_T ;
struct TYPE_19__ {int /*<<< orphan*/ * reader_uri; int /*<<< orphan*/  reader; scalar_t__ rtp_port; int /*<<< orphan*/  control_uri; } ;
typedef  TYPE_4__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_20__ {TYPE_1__* priv; } ;
typedef  TYPE_5__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_21__ {scalar_t__ uri_has_network_info; } ;
typedef  TYPE_6__ VC_CONTAINER_MODULE_T ;
struct TYPE_17__ {TYPE_4__* module; } ;
struct TYPE_16__ {TYPE_6__* module; } ;

/* Variables and functions */
 int DYNAMIC_PORT_ATTEMPTS_MAX ; 
 int /*<<< orphan*/  LOG_ERROR (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  UDP_READ_BUFFER_SIZE ; 
 int /*<<< orphan*/  VC_CONTAINER_CONTROL_IO_SET_READ_BUFFER_SIZE ; 
 int /*<<< orphan*/  VC_CONTAINER_CONTROL_IO_SET_READ_TIMEOUT_MS ; 
 scalar_t__ VC_CONTAINER_ERROR_FORMAT_INVALID ; 
 scalar_t__ VC_CONTAINER_ERROR_OUT_OF_MEMORY ; 
 scalar_t__ VC_CONTAINER_ERROR_URI_OPEN_FAILED ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ rtsp_copy_track_data_from_reader (TYPE_5__*,TYPE_3__*) ; 
 scalar_t__ rtsp_open_file_reader (TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ rtsp_open_network_reader (TYPE_5__*,TYPE_4__*) ; 
 scalar_t__ vc_container_control (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_uri_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_set_host (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rtsp_complete_track( VC_CONTAINER_T *p_ctx,
      VC_CONTAINER_TRACK_T *track )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_MODULE_T *t_module = track->priv->module;
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_SUCCESS;

   if (!t_module->control_uri)
   {
      LOG_ERROR(p_ctx, "RTSP: Track control URI is missing");
      return VC_CONTAINER_ERROR_FORMAT_INVALID;
   }

   if (module->uri_has_network_info)
   {
      int ii;

      if (!vc_uri_set_host(t_module->reader_uri, ""))
      {
         LOG_ERROR(p_ctx, "RTSP: Failed to set track reader URI host");
         return VC_CONTAINER_ERROR_OUT_OF_MEMORY;
      }

      status = rtsp_open_network_reader(p_ctx, t_module);

      for (ii = 0; status == VC_CONTAINER_ERROR_URI_OPEN_FAILED && ii < DYNAMIC_PORT_ATTEMPTS_MAX; ii++)
      {
         /* Reset port to pick up next dynamic port */
         t_module->rtp_port = 0;
         status = rtsp_open_network_reader(p_ctx, t_module);
      }

      /* Change I/O to non-blocking, so that tracks can be polled */
      if (status == VC_CONTAINER_SUCCESS)
         status = vc_container_control(t_module->reader, VC_CONTAINER_CONTROL_IO_SET_READ_TIMEOUT_MS, 0);
      /* Set a large read buffer, to avoid dropping bursts of large packets (e.g. hi-def video) */
      if (status == VC_CONTAINER_SUCCESS)
         status = vc_container_control(t_module->reader, VC_CONTAINER_CONTROL_IO_SET_READ_BUFFER_SIZE, UDP_READ_BUFFER_SIZE);
   } else {
      status = rtsp_open_file_reader(p_ctx, t_module);
   }

   vc_uri_release(t_module->reader_uri);
   t_module->reader_uri = NULL;

   if (status == VC_CONTAINER_SUCCESS)
      status = rtsp_copy_track_data_from_reader(p_ctx, track);

   return status;
}