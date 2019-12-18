#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * video_fifo; int /*<<< orphan*/ * attr_fifo; int /*<<< orphan*/ * audio_fifo; } ;
typedef  TYPE_1__ ffmpeg_t ;

/* Variables and functions */
 int /*<<< orphan*/  fifo_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void deinit_thread_buf(ffmpeg_t *handle)
{
   if (handle->audio_fifo)
   {
      fifo_free(handle->audio_fifo);
      handle->audio_fifo = NULL;
   }

   if (handle->attr_fifo)
   {
      fifo_free(handle->attr_fifo);
      handle->attr_fifo = NULL;
   }

   if (handle->video_fifo)
   {
      fifo_free(handle->video_fifo);
      handle->video_fifo = NULL;
   }
}