#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_6__ {int frames_in_buffer; int planar_buf_frames; int sample_size; scalar_t__ buffer; scalar_t__ planar_buf; scalar_t__ use_float; int /*<<< orphan*/  is_planar; } ;
struct TYPE_5__ {int channels; } ;
struct TYPE_7__ {TYPE_2__ audio; TYPE_1__ params; } ;
typedef  TYPE_3__ ffmpeg_t ;

/* Variables and functions */
 scalar_t__ av_realloc (scalar_t__,int) ; 
 int /*<<< orphan*/  planarize_float (float*,float const*,int) ; 
 int /*<<< orphan*/  planarize_s16 (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static void planarize_audio(ffmpeg_t *handle)
{
   if (!handle->audio.is_planar)
      return;

   if (handle->audio.frames_in_buffer > handle->audio.planar_buf_frames)
   {
      handle->audio.planar_buf = av_realloc(handle->audio.planar_buf,
            handle->audio.frames_in_buffer * handle->params.channels *
            handle->audio.sample_size);
      if (!handle->audio.planar_buf)
         return;

      handle->audio.planar_buf_frames = handle->audio.frames_in_buffer;
   }

   if (handle->audio.use_float)
      planarize_float((float*)handle->audio.planar_buf,
            (const float*)handle->audio.buffer,
            handle->audio.frames_in_buffer);
   else
      planarize_s16((int16_t*)handle->audio.planar_buf,
            (const int16_t*)handle->audio.buffer,
            handle->audio.frames_in_buffer);
}