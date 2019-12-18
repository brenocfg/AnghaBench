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
struct TYPE_7__ {int nb_streams; TYPE_1__** streams; } ;
struct TYPE_6__ {int /*<<< orphan*/  fifo; } ;
struct TYPE_5__ {TYPE_2__* priv_data; } ;
typedef  TYPE_2__ StreamInfo ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_fifo_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mpeg_mux_deinit(AVFormatContext *ctx)
{
    for (int i = 0; i < ctx->nb_streams; i++) {
        StreamInfo *stream = ctx->streams[i]->priv_data;
        if (!stream)
            continue;
        av_fifo_freep(&stream->fifo);
    }
}