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
struct TYPE_3__ {int* linesize; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int av_get_bytes_per_sample (int /*<<< orphan*/ ) ; 
 int av_get_channel_layout_nb_channels (int /*<<< orphan*/ ) ; 
 scalar_t__ av_sample_fmt_is_planar (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int available_samples(AVFrame *out)
{
    int bytes_per_sample = av_get_bytes_per_sample(out->format);
    int samples = out->linesize[0] / bytes_per_sample;

    if (av_sample_fmt_is_planar(out->format)) {
        return samples;
    } else {
        int channels = av_get_channel_layout_nb_channels(out->channel_layout);
        return samples / channels;
    }
}