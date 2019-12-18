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
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;

/* Variables and functions */
 scalar_t__ AV_SAMPLE_FMT_FLT ; 
 scalar_t__ AV_SAMPLE_FMT_S32 ; 
 int av_get_bytes_per_sample (int) ; 
 scalar_t__ av_get_packed_sample_fmt (int) ; 
 scalar_t__ av_sample_fmt_is_planar (int) ; 

__attribute__((used)) static int get_fmt_score(enum AVSampleFormat dst_fmt, enum AVSampleFormat src_fmt)
{
    int score = 0;

    if (av_sample_fmt_is_planar(dst_fmt) != av_sample_fmt_is_planar(src_fmt))
        score ++;

    if (av_get_bytes_per_sample(dst_fmt) < av_get_bytes_per_sample(src_fmt)) {
        score += 100 * (av_get_bytes_per_sample(src_fmt) - av_get_bytes_per_sample(dst_fmt));
    }else
        score += 10  * (av_get_bytes_per_sample(dst_fmt) - av_get_bytes_per_sample(src_fmt));

    if (av_get_packed_sample_fmt(dst_fmt) == AV_SAMPLE_FMT_S32 &&
        av_get_packed_sample_fmt(src_fmt) == AV_SAMPLE_FMT_FLT)
        score += 20;

    if (av_get_packed_sample_fmt(dst_fmt) == AV_SAMPLE_FMT_FLT &&
        av_get_packed_sample_fmt(src_fmt) == AV_SAMPLE_FMT_S32)
        score += 2;

    return score;
}