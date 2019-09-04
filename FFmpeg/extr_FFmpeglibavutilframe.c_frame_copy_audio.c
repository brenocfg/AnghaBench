#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int channels; scalar_t__ nb_samples; scalar_t__ channel_layout; int /*<<< orphan*/  format; int /*<<< orphan*/ * extended_data; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CHECK_CHANNELS_CONSISTENCY (TYPE_1__ const*) ; 
 int /*<<< orphan*/  EINVAL ; 
 int av_sample_fmt_is_planar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_samples_copy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int frame_copy_audio(AVFrame *dst, const AVFrame *src)
{
    int planar   = av_sample_fmt_is_planar(dst->format);
    int channels = dst->channels;
    int planes   = planar ? channels : 1;
    int i;

    if (dst->nb_samples     != src->nb_samples ||
        dst->channels       != src->channels ||
        dst->channel_layout != src->channel_layout)
        return AVERROR(EINVAL);

    CHECK_CHANNELS_CONSISTENCY(src);

    for (i = 0; i < planes; i++)
        if (!dst->extended_data[i] || !src->extended_data[i])
            return AVERROR(EINVAL);

    av_samples_copy(dst->extended_data, src->extended_data, 0, 0,
                    dst->nb_samples, channels, dst->format);

    return 0;
}