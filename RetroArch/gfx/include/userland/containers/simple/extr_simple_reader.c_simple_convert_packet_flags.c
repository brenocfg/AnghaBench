#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {TYPE_3__** tracks; } ;
typedef  TYPE_4__ VC_CONTAINER_T ;
struct TYPE_8__ {TYPE_2__* priv; } ;
struct TYPE_7__ {TYPE_1__* module; } ;
struct TYPE_6__ {int variant; } ;

/* Variables and functions */
#define  VARIANT_MMAL 129 
#define  VARIANT_OMX 128 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_CONFIG ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_DISCONTINUITY ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_ENCRYPTED ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME_END ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_FRAME_START ; 
 int /*<<< orphan*/  VC_CONTAINER_PACKET_FLAG_KEYFRAME ; 

__attribute__((used)) static uint32_t simple_convert_packet_flags(VC_CONTAINER_T *ctx,
   unsigned int track_num, uint32_t flags)
{
   typedef struct { uint32_t from; uint32_t to; } convert_from_t;
   const convert_from_t convert_from_mmal[] =
   { {1<<1, VC_CONTAINER_PACKET_FLAG_FRAME_START},
     {1<<2, VC_CONTAINER_PACKET_FLAG_FRAME_END},
     {1<<3, VC_CONTAINER_PACKET_FLAG_KEYFRAME},
     {1<<4, VC_CONTAINER_PACKET_FLAG_DISCONTINUITY},
     {1<<5, VC_CONTAINER_PACKET_FLAG_CONFIG},
     {1<<6, VC_CONTAINER_PACKET_FLAG_ENCRYPTED},
     {0, 0} };
   const convert_from_t convert_from_omx[] =
   { {0x10, VC_CONTAINER_PACKET_FLAG_FRAME_END},
     {0x20, VC_CONTAINER_PACKET_FLAG_KEYFRAME},
     {0x80, VC_CONTAINER_PACKET_FLAG_CONFIG},
     {0, 0} };
   const convert_from_t *convert_from = NULL;
   int i;

   switch (ctx->tracks[track_num]->priv->module->variant)
   {
      case VARIANT_MMAL: convert_from = convert_from_mmal; break;
      case VARIANT_OMX: convert_from = convert_from_omx; break;
      default: break;
   }

   if (convert_from)
   {
      uint32_t new_flags = 0;
      for (i = 0; convert_from[i].from; i++)
         if (convert_from[i].from & flags)
            new_flags |= convert_from[i].to;
      return new_flags;
   }

   return flags;
}