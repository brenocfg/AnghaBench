#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_22__ {int nb_samples; int /*<<< orphan*/ * linesize; } ;
struct TYPE_21__ {int in_sample_rate; scalar_t__ out_sample_rate; } ;
typedef  TYPE_1__ SwrContext ;
typedef  TYPE_2__ AVFrame ;

/* Variables and functions */
 int av_frame_get_buffer (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int available_samples (TYPE_2__*) ; 
 int config_changed (TYPE_1__*,TYPE_2__*,TYPE_2__ const*) ; 
 int convert_frame (TYPE_1__*,TYPE_2__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  swr_close (TYPE_1__*) ; 
 int swr_config_frame (TYPE_1__*,TYPE_2__*,TYPE_2__ const*) ; 
 int swr_get_delay (TYPE_1__*,scalar_t__) ; 
 int swr_init (TYPE_1__*) ; 
 int /*<<< orphan*/  swr_is_initialized (TYPE_1__*) ; 

int swr_convert_frame(SwrContext *s,
                      AVFrame *out, const AVFrame *in)
{
    int ret, setup = 0;

    if (!swr_is_initialized(s)) {
        if ((ret = swr_config_frame(s, out, in)) < 0)
            return ret;
        if ((ret = swr_init(s)) < 0)
            return ret;
        setup = 1;
    } else {
        // return as is or reconfigure for input changes?
        if ((ret = config_changed(s, out, in)))
            return ret;
    }

    if (out) {
        if (!out->linesize[0]) {
            out->nb_samples = swr_get_delay(s, s->out_sample_rate) + 3;
            if (in) {
                out->nb_samples += in->nb_samples*(int64_t)s->out_sample_rate / s->in_sample_rate;
            }
            if ((ret = av_frame_get_buffer(out, 0)) < 0) {
                if (setup)
                    swr_close(s);
                return ret;
            }
        } else {
            if (!out->nb_samples)
                out->nb_samples = available_samples(out);
        }
    }

    return convert_frame(s, out, in);
}