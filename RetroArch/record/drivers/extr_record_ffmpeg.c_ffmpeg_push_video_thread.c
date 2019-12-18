#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct record_video_data {int /*<<< orphan*/  is_dupe; } ;
struct TYPE_12__ {int /*<<< orphan*/  frame_cnt; TYPE_9__* conv_frame; } ;
struct TYPE_11__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_13__ {TYPE_2__ video; TYPE_1__ muxer; } ;
typedef  TYPE_3__ ffmpeg_t ;
struct TYPE_15__ {int /*<<< orphan*/  pts; } ;
struct TYPE_14__ {scalar_t__ size; } ;
typedef  TYPE_4__ AVPacket ;

/* Variables and functions */
 scalar_t__ av_interleaved_write_frame (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  encode_video (TYPE_3__*,TYPE_4__*,TYPE_9__*) ; 
 int /*<<< orphan*/  ffmpeg_scale_input (TYPE_3__*,struct record_video_data const*) ; 

__attribute__((used)) static bool ffmpeg_push_video_thread(ffmpeg_t *handle,
      const struct record_video_data *vid)
{
   AVPacket pkt;

   if (!vid->is_dupe)
      ffmpeg_scale_input(handle, vid);

   handle->video.conv_frame->pts = handle->video.frame_cnt;

   if (!encode_video(handle, &pkt, handle->video.conv_frame))
      return false;

   if (pkt.size)
   {
      if (av_interleaved_write_frame(handle->muxer.ctx, &pkt) < 0)
         return false;
   }

   handle->video.frame_cnt++;
   return true;
}