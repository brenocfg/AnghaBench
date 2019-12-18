#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint16_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_13__ {TYPE_5__* format; TYPE_4__* priv; } ;
typedef  TYPE_6__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_12__ {int bitrate; int /*<<< orphan*/  extradata; int /*<<< orphan*/  extradata_size; TYPE_2__* type; int /*<<< orphan*/  codec; } ;
struct TYPE_11__ {TYPE_3__* module; } ;
struct TYPE_10__ {int /*<<< orphan*/  extradata; } ;
struct TYPE_8__ {int sample_rate; void* bits_per_sample; void* block_align; void* channels; } ;
struct TYPE_9__ {TYPE_1__ audio; } ;

/* Variables and functions */
 scalar_t__ ASF_EXTRADATA_MAX ; 
 int /*<<< orphan*/  ASF_READ_BYTES (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 void* ASF_READ_U16 (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int ASF_READ_U32 (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/  CHECK_POINT (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_CORRUPTED ; 
 int /*<<< orphan*/  VC_CONTAINER_SUCCESS ; 
 int /*<<< orphan*/  waveformat_to_codec (void*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T asf_read_waveformatex( VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_TRACK_T *p_track, int64_t size)
{
   uint16_t extradata_size;

   /* Read WAVEFORMATEX structure */
   p_track->format->codec = waveformat_to_codec(ASF_READ_U16(p_ctx, size, "Codec ID"));
   p_track->format->type->audio.channels = ASF_READ_U16(p_ctx, size, "Number of Channels");
   p_track->format->type->audio.sample_rate = ASF_READ_U32(p_ctx, size, "Samples per Second");
   p_track->format->bitrate = ASF_READ_U32(p_ctx, size, "Average Number of Bytes Per Second") * 8;
   p_track->format->type->audio.block_align = ASF_READ_U16(p_ctx, size, "Block Alignment");
   p_track->format->type->audio.bits_per_sample = ASF_READ_U16(p_ctx, size, "Bits Per Sample");
   extradata_size = ASF_READ_U16(p_ctx, size, "Codec Specific Data Size");

   CHECK_POINT(p_ctx, size);

   if(!extradata_size) return VC_CONTAINER_SUCCESS;

   /* Sanity check the size of the data */
   if(extradata_size > size) return VC_CONTAINER_ERROR_CORRUPTED;

   if(extradata_size > ASF_EXTRADATA_MAX)
   {
      LOG_DEBUG(p_ctx, "extradata truncated");
      extradata_size = ASF_EXTRADATA_MAX;
   }
   p_track->format->extradata = p_track->priv->module->extradata;
   p_track->format->extradata_size = ASF_READ_BYTES(p_ctx, size, p_track->format->extradata, extradata_size);

   return STREAM_STATUS(p_ctx);
}