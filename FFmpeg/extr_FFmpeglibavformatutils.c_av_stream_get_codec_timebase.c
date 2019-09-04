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
struct TYPE_7__ {TYPE_2__* internal; } ;
struct TYPE_6__ {TYPE_1__* avctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  time_base; } ;
typedef  TYPE_3__ AVStream ;
typedef  int /*<<< orphan*/  AVRational ;

/* Variables and functions */

AVRational av_stream_get_codec_timebase(const AVStream *st)
{
    // See avformat_transfer_internal_stream_timing_info() TODO.
#if FF_API_LAVF_AVCTX
FF_DISABLE_DEPRECATION_WARNINGS
    return st->codec->time_base;
FF_ENABLE_DEPRECATION_WARNINGS
#else
    return st->internal->avctx->time_base;
#endif
}