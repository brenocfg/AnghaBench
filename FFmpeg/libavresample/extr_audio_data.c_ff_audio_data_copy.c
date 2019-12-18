#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ channels; int nb_samples; int planes; int stride; int /*<<< orphan*/ * data; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  is_planar; } ;
struct TYPE_8__ {size_t* channel_map; int* channel_copy; scalar_t__* channel_zero; scalar_t__ do_zero; scalar_t__ do_copy; scalar_t__ do_remap; } ;
typedef  TYPE_1__ ChannelMapInfo ;
typedef  TYPE_2__ AudioData ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  av_samples_set_silence (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int ff_audio_data_realloc (TYPE_2__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int ff_audio_data_copy(AudioData *dst, AudioData *src, ChannelMapInfo *map)
{
    int ret, p;

    /* validate input/output compatibility */
    if (dst->sample_fmt != src->sample_fmt || dst->channels < src->channels)
        return AVERROR(EINVAL);

    if (map && !src->is_planar) {
        av_log(src, AV_LOG_ERROR, "cannot remap packed format during copy\n");
        return AVERROR(EINVAL);
    }

    /* if the input is empty, just empty the output */
    if (!src->nb_samples) {
        dst->nb_samples = 0;
        return 0;
    }

    /* reallocate output if necessary */
    ret = ff_audio_data_realloc(dst, src->nb_samples);
    if (ret < 0)
        return ret;

    /* copy data */
    if (map) {
        if (map->do_remap) {
            for (p = 0; p < src->planes; p++) {
                if (map->channel_map[p] >= 0)
                    memcpy(dst->data[p], src->data[map->channel_map[p]],
                           src->nb_samples * src->stride);
            }
        }
        if (map->do_copy || map->do_zero) {
            for (p = 0; p < src->planes; p++) {
                if (map->channel_copy[p])
                    memcpy(dst->data[p], dst->data[map->channel_copy[p]],
                           src->nb_samples * src->stride);
                else if (map->channel_zero[p])
                    av_samples_set_silence(&dst->data[p], 0, src->nb_samples,
                                           1, dst->sample_fmt);
            }
        }
    } else {
        for (p = 0; p < src->planes; p++)
            memcpy(dst->data[p], src->data[p], src->nb_samples * src->stride);
    }

    dst->nb_samples = src->nb_samples;

    return 0;
}