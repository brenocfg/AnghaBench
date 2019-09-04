#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct video_data {scalar_t__ buffers; int /*<<< orphan*/  fd; int /*<<< orphan*/  buffers_queued; } ;
struct TYPE_4__ {struct video_data* priv_data; } ;
typedef  TYPE_1__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ atomic_load (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mmap_close (struct video_data*) ; 
 int /*<<< orphan*/  v4l2_close (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int v4l2_read_close(AVFormatContext *ctx)
{
    struct video_data *s = ctx->priv_data;

    if (atomic_load(&s->buffers_queued) != s->buffers)
        av_log(ctx, AV_LOG_WARNING, "Some buffers are still owned by the caller on "
               "close.\n");

    mmap_close(s);

    v4l2_close(s->fd);
    return 0;
}