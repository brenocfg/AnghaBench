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
typedef  int /*<<< orphan*/  uint8_t ;
struct record_video_data {scalar_t__ width; scalar_t__ height; int pitch; int /*<<< orphan*/  data; } ;
struct TYPE_8__ {TYPE_2__* conv_frame; int /*<<< orphan*/  scaler; int /*<<< orphan*/  sws; int /*<<< orphan*/  pix_fmt; int /*<<< orphan*/  in_pix_fmt; scalar_t__ use_sws; } ;
struct TYPE_6__ {scalar_t__ out_width; scalar_t__ out_height; } ;
struct TYPE_9__ {TYPE_3__ video; TYPE_1__ params; } ;
typedef  TYPE_4__ ffmpeg_t ;
struct TYPE_7__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWS_BILINEAR ; 
 int /*<<< orphan*/  SWS_POINT ; 
 int /*<<< orphan*/  sws_getCachedContext (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sws_scale (int /*<<< orphan*/ ,int /*<<< orphan*/  const* const*,int*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  video_frame_record_scale (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int) ; 

__attribute__((used)) static void ffmpeg_scale_input(ffmpeg_t *handle,
      const struct record_video_data *vid)
{
   /* Attempt to preserve more information if we scale down. */
   bool shrunk = handle->params.out_width < vid->width
      || handle->params.out_height < vid->height;

   if (handle->video.use_sws)
   {
      int linesize = vid->pitch;

      handle->video.sws = sws_getCachedContext(handle->video.sws,
            vid->width, vid->height, handle->video.in_pix_fmt,
            handle->params.out_width, handle->params.out_height,
            handle->video.pix_fmt,
            shrunk ? SWS_BILINEAR : SWS_POINT, NULL, NULL, NULL);

      sws_scale(handle->video.sws, (const uint8_t* const*)&vid->data,
            &linesize, 0, vid->height, handle->video.conv_frame->data,
            handle->video.conv_frame->linesize);
   }
   else
   {
      video_frame_record_scale(
            &handle->video.scaler,
            handle->video.conv_frame->data[0],
            vid->data,
            handle->params.out_width,
            handle->params.out_height,
            handle->video.conv_frame->linesize[0],
            vid->width,
            vid->height,
            vid->pitch,
            shrunk);
   }
}