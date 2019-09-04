#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ codec_id; } ;
struct TYPE_10__ {scalar_t__ codec_id; } ;
struct TYPE_9__ {int nb_streams; TYPE_2__** streams; } ;
struct TYPE_8__ {TYPE_1__* internal; TYPE_6__* codecpar; int /*<<< orphan*/ * parser; } ;
struct TYPE_7__ {scalar_t__ need_context_update; TYPE_5__* avctx; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_parser_close (int /*<<< orphan*/ *) ; 
 int avcodec_parameters_to_context (TYPE_5__*,TYPE_6__*) ; 

__attribute__((used)) static int update_stream_avctx(AVFormatContext *s)
{
    int i, ret;
    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];

        if (!st->internal->need_context_update)
            continue;

        /* close parser, because it depends on the codec */
        if (st->parser && st->internal->avctx->codec_id != st->codecpar->codec_id) {
            av_parser_close(st->parser);
            st->parser = NULL;
        }

        /* update internal codec context, for the parser */
        ret = avcodec_parameters_to_context(st->internal->avctx, st->codecpar);
        if (ret < 0)
            return ret;

#if FF_API_LAVF_AVCTX
FF_DISABLE_DEPRECATION_WARNINGS
        /* update deprecated public codec context */
        ret = avcodec_parameters_to_context(st->codec, st->codecpar);
        if (ret < 0)
            return ret;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

        st->internal->need_context_update = 0;
    }
    return 0;
}