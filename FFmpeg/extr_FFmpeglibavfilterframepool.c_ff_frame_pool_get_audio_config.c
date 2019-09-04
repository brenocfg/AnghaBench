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
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;
struct TYPE_3__ {scalar_t__ type; int channels; int nb_samples; int format; int align; } ;
typedef  TYPE_1__ FFFramePool ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_assert0 (int) ; 

int ff_frame_pool_get_audio_config(FFFramePool *pool,
                                   int *channels,
                                   int *nb_samples,
                                   enum AVSampleFormat *format,
                                   int *align)
{
    if (!pool)
        return AVERROR(EINVAL);

    av_assert0(pool->type == AVMEDIA_TYPE_AUDIO);

    *channels = pool->channels;
    *nb_samples = pool->nb_samples;
    *format = pool->format;
    *align = pool->align;

    return 0;
}