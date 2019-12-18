#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_14__ {size_t tracks_num; TYPE_2__* priv; TYPE_1__** tracks; } ;
typedef  TYPE_3__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_15__ {size_t track; int flags; } ;
typedef  TYPE_4__ VC_CONTAINER_PACKET_T ;
struct TYPE_13__ {scalar_t__ (* pf_read ) (TYPE_3__*,TYPE_4__*,int) ;scalar_t__ drm_filter; } ;
struct TYPE_12__ {int /*<<< orphan*/  is_enabled; } ;

/* Variables and functions */
 scalar_t__ VC_CONTAINER_ERROR_CONTINUE ; 
 int VC_CONTAINER_PACKET_FLAG_ENCRYPTED ; 
 int VC_CONTAINER_READ_FLAG_INFO ; 
 int VC_CONTAINER_READ_FLAG_SKIP ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 scalar_t__ stub1 (TYPE_3__*,TYPE_4__*,int) ; 
 scalar_t__ stub2 (TYPE_3__*,TYPE_4__*,int) ; 
 scalar_t__ vc_container_filter_process (scalar_t__,TYPE_4__*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T container_read_packet( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_PACKET_T *p_packet, uint32_t flags )
{
   VC_CONTAINER_STATUS_T status;

   while(1)
   {
      status = p_ctx->priv->pf_read(p_ctx, p_packet, flags);
      if(status == VC_CONTAINER_ERROR_CONTINUE)
         continue;

      if(!p_packet || (flags & VC_CONTAINER_READ_FLAG_SKIP))
         return status; /* We've just been requested to skip the data */

      if(status != VC_CONTAINER_SUCCESS)
         return status;

      /* Skip data from out of bounds tracks, disabled tracks or packets that are encrypted
         and cannot be decrypted */
      if(p_packet->track >= p_ctx->tracks_num ||
         !p_ctx->tracks[p_packet->track]->is_enabled ||
         ((p_packet->flags & VC_CONTAINER_PACKET_FLAG_ENCRYPTED) && !p_ctx->priv->drm_filter))
      {
         if(flags & VC_CONTAINER_READ_FLAG_INFO)
            status = p_ctx->priv->pf_read(p_ctx, p_packet, VC_CONTAINER_READ_FLAG_SKIP);
         if(status == VC_CONTAINER_SUCCESS || status == VC_CONTAINER_ERROR_CONTINUE)
            continue;
      }
      if(status != VC_CONTAINER_SUCCESS)
         return status;

      if(p_ctx->priv->drm_filter)
         status = vc_container_filter_process(p_ctx->priv->drm_filter, p_packet);

      break;
   }
   return status;
}