#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_8__ {TYPE_1__ muxer; } ;
typedef  TYPE_2__ ffmpeg_t ;
struct TYPE_9__ {int /*<<< orphan*/  pb; } ;

/* Variables and functions */
 int /*<<< orphan*/  av_write_trailer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_close (int /*<<< orphan*/ ) ; 
 TYPE_6__* ctx ; 
 int /*<<< orphan*/  deinit_thread (TYPE_2__*) ; 
 int /*<<< orphan*/  deinit_thread_buf (TYPE_2__*) ; 
 int /*<<< orphan*/  ffmpeg_flush_buffers (TYPE_2__*) ; 

__attribute__((used)) static bool ffmpeg_finalize(void *data)
{
   ffmpeg_t *handle = (ffmpeg_t*)data;
   if (!handle)
      return false;

   deinit_thread(handle);

   /* Flush out data still in buffers (internal, and FFmpeg internal). */
   ffmpeg_flush_buffers(handle);

   deinit_thread_buf(handle);

   /* Write final data. */
   av_write_trailer(handle->muxer.ctx);

   avio_close(ctx->pb);

   return true;
}