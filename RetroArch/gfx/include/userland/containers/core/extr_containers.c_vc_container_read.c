#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  VC_PACKETIZER_T ;
typedef  int VC_PACKETIZER_FLAGS_T ;
struct TYPE_16__ {size_t tracks_num; scalar_t__ position; TYPE_3__* priv; TYPE_2__** tracks; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
typedef  scalar_t__ VC_CONTAINER_STATUS_T ;
struct TYPE_17__ {size_t track; scalar_t__ dts; scalar_t__ pts; scalar_t__ size; int /*<<< orphan*/  buffer_size; int /*<<< orphan*/  data; } ;
typedef  TYPE_5__ VC_CONTAINER_PACKET_T ;
struct TYPE_15__ {int /*<<< orphan*/  packetizer_buffer; TYPE_5__ packetizer_packet; int /*<<< orphan*/  packetizing; } ;
struct TYPE_14__ {TYPE_1__* priv; int /*<<< orphan*/  is_enabled; } ;
struct TYPE_13__ {int /*<<< orphan*/ * packetizer; } ;

/* Variables and functions */
 int /*<<< orphan*/  PACKETIZER_BUFFER_SIZE ; 
 scalar_t__ VC_CONTAINER_ERROR_CONTINUE ; 
 scalar_t__ VC_CONTAINER_ERROR_INVALID_ARGUMENT ; 
 int VC_CONTAINER_READ_FLAG_FORCE_TRACK ; 
 int VC_CONTAINER_READ_FLAG_INFO ; 
 int VC_CONTAINER_READ_FLAG_SKIP ; 
 scalar_t__ VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  VC_PACKETIZER_FLAG_FORCE_RELEASE_INPUT ; 
 int VC_PACKETIZER_FLAG_INFO ; 
 int VC_PACKETIZER_FLAG_SKIP ; 
 scalar_t__ container_read_packet (TYPE_4__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  vc_packetizer_pop (int /*<<< orphan*/ *,TYPE_5__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_packetizer_push (int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ vc_packetizer_read (int /*<<< orphan*/ *,TYPE_5__*,int) ; 

VC_CONTAINER_STATUS_T vc_container_read( VC_CONTAINER_T *p_ctx, VC_CONTAINER_PACKET_T *p_packet, uint32_t flags )
{
   VC_CONTAINER_STATUS_T status = VC_CONTAINER_ERROR_CONTINUE;
   VC_PACKETIZER_FLAGS_T packetizer_flags = 0;
   VC_PACKETIZER_T *packetizer;
   uint32_t force = flags & VC_CONTAINER_READ_FLAG_FORCE_TRACK;
   unsigned int i;

   if(!p_packet && !(flags & VC_CONTAINER_READ_FLAG_SKIP))
      return VC_CONTAINER_ERROR_INVALID_ARGUMENT;
   if(!p_packet && (flags & VC_CONTAINER_READ_FLAG_INFO))
      return VC_CONTAINER_ERROR_INVALID_ARGUMENT;
   if(p_packet && !p_packet->data && !(flags & (VC_CONTAINER_READ_FLAG_INFO | VC_CONTAINER_READ_FLAG_SKIP)))
      return VC_CONTAINER_ERROR_INVALID_ARGUMENT;
   if((flags & VC_CONTAINER_READ_FLAG_FORCE_TRACK) &&
      (!p_packet || p_packet->track >= p_ctx->tracks_num || !p_ctx->tracks[p_packet->track]->is_enabled))
      return VC_CONTAINER_ERROR_INVALID_ARGUMENT;

   /* Always having a packet structure to work with simplifies things */
   if(!p_packet)
      p_packet = &p_ctx->priv->packetizer_packet;

   /* Simple/Fast case first */
   if(!p_ctx->priv->packetizing)
   {
      status = container_read_packet( p_ctx, p_packet, flags );
      goto end;
   }

   if(flags & VC_CONTAINER_READ_FLAG_INFO)
      packetizer_flags |= VC_PACKETIZER_FLAG_INFO;
   if(flags & VC_CONTAINER_READ_FLAG_SKIP)
      packetizer_flags |= VC_PACKETIZER_FLAG_SKIP;

   /* Loop through all the packetized tracks first to see if we've got any
    * data to consume there */
   for(i = 0; i < p_ctx->tracks_num; i++)
   {
      VC_PACKETIZER_T *packetizer = p_ctx->tracks[i]->priv->packetizer;
      if(!p_ctx->tracks[i]->is_enabled || !packetizer ||
         (force && i != p_packet->track))
         continue;

      status = vc_packetizer_read(packetizer, p_packet, packetizer_flags);
      p_packet->track = i;
      if(status == VC_CONTAINER_SUCCESS)
         break;
   }
   if(i < p_ctx->tracks_num) /* We've got some data */
      goto end;

   /* Let's go and read some data from the actual container */
   while(1)
   {
      VC_CONTAINER_PACKET_T *tmp = &p_ctx->priv->packetizer_packet;
      tmp->track = p_packet->track;

      /* Let's check what the container has to offer */
      status = container_read_packet( p_ctx, tmp, force|VC_PACKETIZER_FLAG_INFO );
      if(status != VC_CONTAINER_SUCCESS)
         return status;

      if(!p_ctx->tracks[tmp->track]->priv->packetizer)
      {
         status = container_read_packet( p_ctx, p_packet, flags );
         break;
      }

      /* Feed data from the container onto the packetizer */
      packetizer = p_ctx->tracks[tmp->track]->priv->packetizer;

      tmp->data = p_ctx->priv->packetizer_buffer;
      tmp->buffer_size = PACKETIZER_BUFFER_SIZE;
      tmp->size = 0;
      status = container_read_packet( p_ctx, tmp, force );
      if(status != VC_CONTAINER_SUCCESS)
         return status;

      p_packet->track = tmp->track;
      vc_packetizer_push(packetizer, tmp);
      vc_packetizer_pop(packetizer, &tmp, VC_PACKETIZER_FLAG_FORCE_RELEASE_INPUT);

      status = vc_packetizer_read(packetizer, p_packet, packetizer_flags);
      if(status == VC_CONTAINER_SUCCESS)
         break;
   }

 end:
   if(status != VC_CONTAINER_SUCCESS)
      return status;

   if(p_packet && p_packet->dts > p_ctx->position)
      p_ctx->position = p_packet->dts;
   if(p_packet && p_packet->pts > p_ctx->position)
      p_ctx->position = p_packet->pts;

   return VC_CONTAINER_SUCCESS;
}