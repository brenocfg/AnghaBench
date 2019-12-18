#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ framework_data; struct TYPE_10__* next; TYPE_1__* priv; scalar_t__ out; scalar_t__ in; } ;
typedef  TYPE_2__ VC_PACKETIZER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  TYPE_2__ VC_CONTAINER_PACKET_T ;
struct TYPE_11__ {TYPE_2__* first; } ;
typedef  TYPE_4__ VC_CONTAINER_BYTESTREAM_T ;
struct TYPE_9__ {scalar_t__ module_handle; int /*<<< orphan*/  (* pf_close ) (TYPE_2__*) ;TYPE_4__ stream; } ;

/* Variables and functions */
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  vc_container_format_delete (scalar_t__) ; 
 int /*<<< orphan*/  vc_packetizer_unload (TYPE_2__*) ; 

VC_CONTAINER_STATUS_T vc_packetizer_close( VC_PACKETIZER_T *p_ctx )
{
   VC_CONTAINER_BYTESTREAM_T *stream;
   VC_CONTAINER_PACKET_T *packet, *next;

   if(!p_ctx) return VC_CONTAINER_SUCCESS;

   stream = &p_ctx->priv->stream;

   if(p_ctx->in) vc_container_format_delete(p_ctx->in);
   if(p_ctx->out) vc_container_format_delete(p_ctx->out);
   if(p_ctx->priv->pf_close) p_ctx->priv->pf_close(p_ctx);
   if(p_ctx->priv->module_handle) vc_packetizer_unload(p_ctx);

   /* Free the bytestream  */
   for(packet = stream->first; packet; packet = next)
   {
      next = packet->next;
      if(packet->framework_data) free(packet);
   }

   free(p_ctx);
   return VC_CONTAINER_SUCCESS;
}