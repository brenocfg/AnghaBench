#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {TYPE_4__* format; } ;
typedef  TYPE_5__ VC_CONTAINER_TRACK_T ;
struct TYPE_20__ {TYPE_5__** tracks; TYPE_1__* priv; } ;
typedef  TYPE_6__ VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
struct TYPE_21__ {size_t current_track; } ;
typedef  TYPE_7__ VC_CONTAINER_MODULE_T ;
struct TYPE_18__ {int extradata_size; int es_type; int codec; int /*<<< orphan*/  extradata; int /*<<< orphan*/  bitrate; TYPE_3__* type; } ;
struct TYPE_16__ {int sample_rate; } ;
struct TYPE_17__ {TYPE_2__ audio; } ;
struct TYPE_15__ {TYPE_7__* module; } ;

/* Variables and functions */
 unsigned int MP4_GET_DESCRIPTOR_SIZE (int) ; 
 int /*<<< orphan*/  MP4_WRITE_DESCRIPTOR_HEADER (int,int) ; 
 int /*<<< orphan*/  STREAM_STATUS (TYPE_6__*) ; 
#define  VC_CONTAINER_CODEC_JPEG 136 
#define  VC_CONTAINER_CODEC_MP1V 135 
#define  VC_CONTAINER_CODEC_MP2V 134 
#define  VC_CONTAINER_CODEC_MP4A 133 
#define  VC_CONTAINER_CODEC_MP4V 132 
#define  VC_CONTAINER_CODEC_MPGA 131 
 int /*<<< orphan*/  VC_CONTAINER_ERROR_TRACK_FORMAT_NOT_SUPPORTED ; 
#define  VC_CONTAINER_ES_TYPE_AUDIO 130 
#define  VC_CONTAINER_ES_TYPE_SUBPICTURE 129 
#define  VC_CONTAINER_ES_TYPE_VIDEO 128 
 int /*<<< orphan*/  WRITE_BYTES (TYPE_6__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WRITE_U16 (TYPE_6__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U24 (TYPE_6__*,int,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U8 (TYPE_6__*,int,char*) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T mp4_write_box_esds( VC_CONTAINER_T *p_ctx )
{
   VC_CONTAINER_MODULE_T *module = p_ctx->priv->module;
   VC_CONTAINER_TRACK_T *track = p_ctx->tracks[module->current_track];
   unsigned int decoder_specific_size = 0, decoder_config_size, sl_size;
   unsigned int stream_type, object_type;

#define MP4_GET_DESCRIPTOR_SIZE(size) \
   ((size) < 0x0080) ? 2 + (size) : ((size) < 0x4000) ? 3 + (size) : 4 + (size)
#define MP4_WRITE_DESCRIPTOR_HEADER(type, size) \
   LOG_FORMAT(p_ctx, "descriptor %x, size %i", type, size); _WRITE_U8(p_ctx, type); \
   if((size) >= 0x4000) _WRITE_U8(p_ctx, (((size) >> 14) & 0x7F) | 0x80); \
   if((size) >= 0x80  ) _WRITE_U8(p_ctx, (((size) >> 7 ) & 0x7F) | 0x80); \
   _WRITE_U8(p_ctx, (size) & 0x7F)

   /* We only support small size descriptors */
   if(track->format->extradata_size > 0x200000 - 100)
      return VC_CONTAINER_ERROR_TRACK_FORMAT_NOT_SUPPORTED;

   switch(track->format->es_type)
   {
   case VC_CONTAINER_ES_TYPE_VIDEO: stream_type = 0x4; break;
   case VC_CONTAINER_ES_TYPE_AUDIO: stream_type = 0x5; break;
   case VC_CONTAINER_ES_TYPE_SUBPICTURE: stream_type = 0x20; break;
   default: return VC_CONTAINER_ERROR_TRACK_FORMAT_NOT_SUPPORTED;
   }
   switch(track->format->codec)
   {
   case VC_CONTAINER_CODEC_MP4V: object_type = 0x20; break;
   case VC_CONTAINER_CODEC_MP1V: object_type = 0x6B; break;
   case VC_CONTAINER_CODEC_MP2V: object_type = 0x60; break;
   case VC_CONTAINER_CODEC_JPEG: object_type = 0x6C; break;
   case VC_CONTAINER_CODEC_MP4A: object_type = 0x40; break;
   case VC_CONTAINER_CODEC_MPGA:
      object_type = track->format->type->audio.sample_rate < 32000 ? 0x69 : 0x6B; break;
   default: return VC_CONTAINER_ERROR_TRACK_FORMAT_NOT_SUPPORTED;
   }

   decoder_specific_size = MP4_GET_DESCRIPTOR_SIZE(track->format->extradata_size);
   decoder_config_size = MP4_GET_DESCRIPTOR_SIZE(13 + decoder_specific_size);
   sl_size = MP4_GET_DESCRIPTOR_SIZE(1);

   WRITE_U8(p_ctx,  0, "version");
   WRITE_U24(p_ctx, 0, "flags");

   /* Write the ES descriptor */
   MP4_WRITE_DESCRIPTOR_HEADER(0x3, 3 + decoder_config_size + sl_size);
   WRITE_U16(p_ctx, module->current_track + 1, "es_id");
   WRITE_U8(p_ctx, 0x1f, "flags"); /* stream_priority = 0x1f */

   /* Write the Decoder Config descriptor */
   MP4_WRITE_DESCRIPTOR_HEADER(0x4, 13 + decoder_specific_size);
   WRITE_U8(p_ctx, object_type, "object_type_indication");
   WRITE_U8(p_ctx, (stream_type << 2) | 1, "stream_type");
   WRITE_U24(p_ctx, 8000, "buffer_size_db");
   WRITE_U32(p_ctx, track->format->bitrate, "max_bitrate");
   WRITE_U32(p_ctx, track->format->bitrate, "avg_bitrate");
   if(track->format->extradata_size)
   {
      MP4_WRITE_DESCRIPTOR_HEADER(0x5, track->format->extradata_size);
      WRITE_BYTES(p_ctx, track->format->extradata, track->format->extradata_size);
   }

   /* Write the SL descriptor */
   MP4_WRITE_DESCRIPTOR_HEADER(0x6, 1);
   WRITE_U8(p_ctx, 0x2, "flags");

   return STREAM_STATUS(p_ctx);
}