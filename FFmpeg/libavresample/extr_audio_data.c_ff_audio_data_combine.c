#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ sample_fmt; scalar_t__ channels; int nb_samples; int planes; int stride; scalar_t__* data; scalar_t__ read_only; } ;
typedef  TYPE_1__ AudioData ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (TYPE_1__*,int /*<<< orphan*/ ,char*,...) ; 
 int ff_audio_data_realloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,int) ; 

int ff_audio_data_combine(AudioData *dst, int dst_offset, AudioData *src,
                          int src_offset, int nb_samples)
{
    int ret, p, dst_offset2, dst_move_size;

    /* validate input/output compatibility */
    if (dst->sample_fmt != src->sample_fmt || dst->channels != src->channels) {
        av_log(src, AV_LOG_ERROR, "sample format mismatch\n");
        return AVERROR(EINVAL);
    }

    /* validate offsets are within the buffer bounds */
    if (dst_offset < 0 || dst_offset > dst->nb_samples ||
        src_offset < 0 || src_offset > src->nb_samples) {
        av_log(src, AV_LOG_ERROR, "offset out-of-bounds: src=%d dst=%d\n",
               src_offset, dst_offset);
        return AVERROR(EINVAL);
    }

    /* check offsets and sizes to see if we can just do nothing and return */
    if (nb_samples > src->nb_samples - src_offset)
        nb_samples = src->nb_samples - src_offset;
    if (nb_samples <= 0)
        return 0;

    /* validate that the output is not read-only */
    if (dst->read_only) {
        av_log(dst, AV_LOG_ERROR, "dst is read-only\n");
        return AVERROR(EINVAL);
    }

    /* reallocate output if necessary */
    ret = ff_audio_data_realloc(dst, dst->nb_samples + nb_samples);
    if (ret < 0) {
        av_log(dst, AV_LOG_ERROR, "error reallocating dst\n");
        return ret;
    }

    dst_offset2   = dst_offset + nb_samples;
    dst_move_size = dst->nb_samples - dst_offset;

    for (p = 0; p < src->planes; p++) {
        if (dst_move_size > 0) {
            memmove(dst->data[p] + dst_offset2 * dst->stride,
                    dst->data[p] + dst_offset  * dst->stride,
                    dst_move_size * dst->stride);
        }
        memcpy(dst->data[p] + dst_offset * dst->stride,
               src->data[p] + src_offset * src->stride,
               nb_samples * src->stride);
    }
    dst->nb_samples += nb_samples;

    return 0;
}