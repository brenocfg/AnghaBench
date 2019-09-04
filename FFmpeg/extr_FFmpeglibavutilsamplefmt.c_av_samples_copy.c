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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;

/* Variables and functions */
 int av_get_bytes_per_sample (int) ; 
 int av_sample_fmt_is_planar (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  memmove (int /*<<< orphan*/ *,int /*<<< orphan*/ * const,int) ; 

int av_samples_copy(uint8_t **dst, uint8_t * const *src, int dst_offset,
                    int src_offset, int nb_samples, int nb_channels,
                    enum AVSampleFormat sample_fmt)
{
    int planar      = av_sample_fmt_is_planar(sample_fmt);
    int planes      = planar ? nb_channels : 1;
    int block_align = av_get_bytes_per_sample(sample_fmt) * (planar ? 1 : nb_channels);
    int data_size   = nb_samples * block_align;
    int i;

    dst_offset *= block_align;
    src_offset *= block_align;

    if((dst[0] < src[0] ? src[0] - dst[0] : dst[0] - src[0]) >= data_size) {
        for (i = 0; i < planes; i++)
            memcpy(dst[i] + dst_offset, src[i] + src_offset, data_size);
    } else {
        for (i = 0; i < planes; i++)
            memmove(dst[i] + dst_offset, src[i] + src_offset, data_size);
    }

    return 0;
}