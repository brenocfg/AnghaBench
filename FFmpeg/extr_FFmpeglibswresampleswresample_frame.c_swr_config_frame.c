#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  format; int /*<<< orphan*/  channel_layout; } ;
typedef  int /*<<< orphan*/  SwrContext ;
typedef  TYPE_1__ AVFrame ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  av_log (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_opt_set_int (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swr_close (int /*<<< orphan*/ *) ; 

int swr_config_frame(SwrContext *s, const AVFrame *out, const AVFrame *in)
{
    swr_close(s);

    if (in) {
        if (av_opt_set_int(s, "icl", in->channel_layout, 0) < 0)
            goto fail;
        if (av_opt_set_int(s, "isf", in->format, 0) < 0)
            goto fail;
        if (av_opt_set_int(s, "isr", in->sample_rate, 0) < 0)
            goto fail;
    }

    if (out) {
        if (av_opt_set_int(s, "ocl", out->channel_layout, 0) < 0)
            goto fail;
        if (av_opt_set_int(s, "osf", out->format,  0) < 0)
            goto fail;
        if (av_opt_set_int(s, "osr", out->sample_rate, 0) < 0)
            goto fail;
    }

    return 0;
fail:
    av_log(s, AV_LOG_ERROR, "Failed to set option\n");
    return AVERROR(EINVAL);
}