#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int int64_t ;
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EINVAL ; 
 int FFALIGN (int,int) ; 
 int INT_MAX ; 
 int av_get_bytes_per_sample (int) ; 
 int av_sample_fmt_is_planar (int) ; 

int av_samples_get_buffer_size(int *linesize, int nb_channels, int nb_samples,
                               enum AVSampleFormat sample_fmt, int align)
{
    int line_size;
    int sample_size = av_get_bytes_per_sample(sample_fmt);
    int planar      = av_sample_fmt_is_planar(sample_fmt);

    /* validate parameter ranges */
    if (!sample_size || nb_samples <= 0 || nb_channels <= 0)
        return AVERROR(EINVAL);

    /* auto-select alignment if not specified */
    if (!align) {
        if (nb_samples > INT_MAX - 31)
            return AVERROR(EINVAL);
        align = 1;
        nb_samples = FFALIGN(nb_samples, 32);
    }

    /* check for integer overflow */
    if (nb_channels > INT_MAX / align ||
        (int64_t)nb_channels * nb_samples > (INT_MAX - (align * nb_channels)) / sample_size)
        return AVERROR(EINVAL);

    line_size = planar ? FFALIGN(nb_samples * sample_size,               align) :
                         FFALIGN(nb_samples * sample_size * nb_channels, align);
    if (linesize)
        *linesize = line_size;

    return planar ? line_size * nb_channels : line_size;
}