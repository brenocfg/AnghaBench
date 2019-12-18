#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_5__* session_header; TYPE_5__* control_uri; scalar_t__ reader_uri; scalar_t__ reader; } ;
typedef  TYPE_3__ VC_CONTAINER_TRACK_MODULE_T ;
struct TYPE_16__ {unsigned int tracks_num; TYPE_2__* priv; TYPE_7__** tracks; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_17__ {scalar_t__ header_list; struct TYPE_17__* comms_buffer; } ;
typedef  TYPE_5__ VC_CONTAINER_MODULE_T ;
struct TYPE_18__ {TYPE_1__* priv; } ;
struct TYPE_14__ {TYPE_5__* module; } ;
struct TYPE_13__ {TYPE_3__* module; } ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  rtsp_read_response (TYPE_4__*) ; 
 scalar_t__ rtsp_send_teardown_request (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  vc_container_close (scalar_t__) ; 
 int /*<<< orphan*/  vc_container_free_track (TYPE_4__*,TYPE_7__*) ; 
 int /*<<< orphan*/  vc_containers_list_destroy (scalar_t__) ; 
 int /*<<< orphan*/  vc_uri_release (scalar_t__) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T rtsp_reader_close( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   unsigned int i;

   for(i = 0; i < p_ctx->tracks_num; i++)
   {
      VC_CONTAINER_TRACK_MODULE_T *t_module = p_ctx->tracks[i]->priv->module;

      if (t_module->control_uri && t_module->session_header)
      {
         /* Send the teardown message and wait for a response, although it
          * isn't important whether it was successful or not. */
         if (rtsp_send_teardown_request(p_ctx, t_module) == VC_CONTAINER_SUCCESS)
            (void)rtsp_read_response(p_ctx);
      }

      if (t_module->reader)
         vc_container_close(t_module->reader);
      if (t_module->reader_uri)
         vc_uri_release(t_module->reader_uri);
      if (t_module->control_uri)
         free(t_module->control_uri);
      if (t_module->session_header)
         free(t_module->session_header);
      vc_container_free_track(p_ctx, p_ctx->tracks[i]);  /* Also need to close track's reader */
   }
   p_ctx->tracks = NULL;
   p_ctx->tracks_num = 0;
   if (module)
   {
      if (module->comms_buffer)
         free(module->comms_buffer);
      if (module->header_list)
         vc_containers_list_destroy(module->header_list);
      free(module);
   }
   p_ctx->priv->module = 0;
   return VC_CONTAINER_SUCCESS;
}