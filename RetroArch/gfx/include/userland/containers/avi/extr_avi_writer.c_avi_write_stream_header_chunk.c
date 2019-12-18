#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_15__ {TYPE_6__* priv; TYPE_4__* format; int /*<<< orphan*/  is_enabled; } ;
typedef  TYPE_7__ VC_CONTAINER_TRACK_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_STATUS_T ;
typedef  int /*<<< orphan*/  VC_CONTAINER_FOURCC_T ;
struct TYPE_14__ {TYPE_5__* module; } ;
struct TYPE_13__ {int chunk_offs; int chunk_index; int max_chunk_size; int sample_size; } ;
struct TYPE_12__ {scalar_t__ es_type; int bitrate; int /*<<< orphan*/  codec; TYPE_3__* type; } ;
struct TYPE_10__ {int block_align; int sample_rate; } ;
struct TYPE_9__ {int frame_rate_den; int frame_rate_num; scalar_t__ visible_width; scalar_t__ x_offset; scalar_t__ visible_height; scalar_t__ y_offset; } ;
struct TYPE_11__ {TYPE_2__ audio; TYPE_1__ video; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_DEBUG (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  STREAM_STATUS (int /*<<< orphan*/ *) ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_AUDIO ; 
 scalar_t__ VC_CONTAINER_ES_TYPE_VIDEO ; 
 int /*<<< orphan*/  VC_FOURCC (char,unsigned char,char,char) ; 
 int /*<<< orphan*/  WRITE_FOURCC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  WRITE_U16 (int /*<<< orphan*/ *,scalar_t__,char*) ; 
 int /*<<< orphan*/  WRITE_U32 (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  codec_to_vfw_fourcc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_container_assert (int /*<<< orphan*/ ) ; 
 int vc_container_maths_gcd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VC_CONTAINER_STATUS_T avi_write_stream_header_chunk(VC_CONTAINER_T *p_ctx,
   VC_CONTAINER_TRACK_T *track)
{
   VC_CONTAINER_FOURCC_T fourcc_type = 0, fourcc_handler = 0;
   uint32_t flags, scale = 0, rate = 0, div, start = 0, sample_size = 0;
   uint16_t left = 0, right = 0, top = 0, bottom = 0;
   uint32_t max_chunk_size, length = 0;

   WRITE_FOURCC(p_ctx, VC_FOURCC('s','t','r','h'), "Chunk ID");
   WRITE_U32(p_ctx, 56, "Chunk Size");

   if (!track->is_enabled)
      flags = 0; /* AVISF_DISABLED; FIXME: write_media should set this correctly! */
   else
      flags = 0;

   if (track->format->es_type == VC_CONTAINER_ES_TYPE_VIDEO)
   {
      fourcc_type = VC_FOURCC('v','i','d','s');
      sample_size = 0;
      scale = track->format->type->video.frame_rate_den;
      rate = track->format->type->video.frame_rate_num;
      if (rate == 0 || scale == 0)
      {
         LOG_DEBUG(p_ctx, "invalid video framerate (%d/%d)", rate, scale);
         LOG_DEBUG(p_ctx, "using 30/1 (playback timing will almost certainly be incorrect)");
         scale = 1; rate = 30;
      }

      top = track->format->type->video.y_offset;
      left = track->format->type->video.x_offset;
      bottom = track->format->type->video.y_offset + track->format->type->video.visible_height;
      right = track->format->type->video.x_offset + track->format->type->video.visible_width;
   }
   else if (track->format->es_type == VC_CONTAINER_ES_TYPE_AUDIO)
   {
      fourcc_type = VC_FOURCC('a','u','d','s');
      sample_size = track->format->type->audio.block_align;
      scale = 1;

      if (track->format->type->audio.block_align)
         rate = (track->format->bitrate / track->format->type->audio.block_align) >> 3;

      if (rate == 0)
      {
         rate = track->format->type->audio.sample_rate ? track->format->type->audio.sample_rate : 32000;
         LOG_DEBUG(p_ctx, "invalid audio rate, using %d (playback timing will almost certainly be incorrect)",
                   rate);
      }
   }
   else
   {
      /* avi_writer_add_track should ensure this can't happen */
      vc_container_assert(0);
   }

   fourcc_handler = codec_to_vfw_fourcc(track->format->codec);

   div = vc_container_maths_gcd((int64_t)scale, (int64_t)rate);
   scale /= div;
   rate /= div;

   length = sample_size ? track->priv->module->chunk_offs : track->priv->module->chunk_index;
   max_chunk_size = track->priv->module->max_chunk_size;
   track->priv->module->sample_size = sample_size;

   WRITE_FOURCC(p_ctx, fourcc_type, "fccType");
   WRITE_FOURCC(p_ctx, fourcc_handler, "fccHandler");
   WRITE_U32(p_ctx, flags, "dwFlags");
   WRITE_U16(p_ctx, 0, "wPriority");
   WRITE_U16(p_ctx, 0, "wLanguage");
   WRITE_U32(p_ctx, 0, "dwInitialFrames");
   WRITE_U32(p_ctx, scale, "dwScale");
   WRITE_U32(p_ctx, rate, "dwRate");
   WRITE_U32(p_ctx, start, "dwStart");
   WRITE_U32(p_ctx, length, "dwLength");
   WRITE_U32(p_ctx, max_chunk_size, "dwSuggestedBufferSize");
   WRITE_U32(p_ctx, 0, "dwQuality");
   WRITE_U32(p_ctx, sample_size, "dwSampleSize");
   WRITE_U16(p_ctx, left, "rcFrame.left");
   WRITE_U16(p_ctx, top, "rcFrame.top");
   WRITE_U16(p_ctx, right, "rcFrame.right");
   WRITE_U16(p_ctx, bottom, "rcFrame.bottom");

   return STREAM_STATUS(p_ctx);
}