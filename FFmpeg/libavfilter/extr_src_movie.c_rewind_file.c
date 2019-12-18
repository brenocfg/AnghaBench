#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int64_t ;
struct TYPE_10__ {scalar_t__ start_time; } ;
struct TYPE_9__ {int nb_outputs; TYPE_2__* priv; } ;
struct TYPE_8__ {int loop_count; scalar_t__ eof; TYPE_1__* st; TYPE_5__* format_ctx; int /*<<< orphan*/  seek_point; } ;
struct TYPE_7__ {scalar_t__ done; int /*<<< orphan*/  codec_ctx; } ;
typedef  TYPE_2__ MovieContext ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVSEEK_FLAG_BACKWARD ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int /*<<< orphan*/  av_err2str (int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int av_seek_frame (TYPE_5__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avcodec_flush_buffers (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int rewind_file(AVFilterContext *ctx)
{
    MovieContext *movie = ctx->priv;
    int64_t timestamp = movie->seek_point;
    int ret, i;

    if (movie->format_ctx->start_time != AV_NOPTS_VALUE)
        timestamp += movie->format_ctx->start_time;
    ret = av_seek_frame(movie->format_ctx, -1, timestamp, AVSEEK_FLAG_BACKWARD);
    if (ret < 0) {
        av_log(ctx, AV_LOG_ERROR, "Unable to loop: %s\n", av_err2str(ret));
        movie->loop_count = 1; /* do not try again */
        return ret;
    }

    for (i = 0; i < ctx->nb_outputs; i++) {
        avcodec_flush_buffers(movie->st[i].codec_ctx);
        movie->st[i].done = 0;
    }
    movie->eof = 0;
    return 0;
}