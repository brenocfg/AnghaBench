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
struct SwrContext {int log_level_offset; int /*<<< orphan*/  user_out_ch_layout; int /*<<< orphan*/  user_in_ch_layout; void* log_ctx; } ;
typedef  int int64_t ;
typedef  enum AVSampleFormat { ____Placeholder_AVSampleFormat } AVSampleFormat ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int av_get_channel_layout_nb_channels (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (struct SwrContext*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ av_opt_set_int (struct SwrContext*,char*,int,int /*<<< orphan*/ ) ; 
 struct SwrContext* swr_alloc () ; 
 int /*<<< orphan*/  swr_free (struct SwrContext**) ; 

struct SwrContext *swr_alloc_set_opts(struct SwrContext *s,
                                      int64_t out_ch_layout, enum AVSampleFormat out_sample_fmt, int out_sample_rate,
                                      int64_t  in_ch_layout, enum AVSampleFormat  in_sample_fmt, int  in_sample_rate,
                                      int log_offset, void *log_ctx){
    if(!s) s= swr_alloc();
    if(!s) return NULL;

    s->log_level_offset= log_offset;
    s->log_ctx= log_ctx;

    if (av_opt_set_int(s, "ocl", out_ch_layout,   0) < 0)
        goto fail;

    if (av_opt_set_int(s, "osf", out_sample_fmt,  0) < 0)
        goto fail;

    if (av_opt_set_int(s, "osr", out_sample_rate, 0) < 0)
        goto fail;

    if (av_opt_set_int(s, "icl", in_ch_layout,    0) < 0)
        goto fail;

    if (av_opt_set_int(s, "isf", in_sample_fmt,   0) < 0)
        goto fail;

    if (av_opt_set_int(s, "isr", in_sample_rate,  0) < 0)
        goto fail;

    if (av_opt_set_int(s, "ich", av_get_channel_layout_nb_channels(s-> user_in_ch_layout), 0) < 0)
        goto fail;

    if (av_opt_set_int(s, "och", av_get_channel_layout_nb_channels(s->user_out_ch_layout), 0) < 0)
        goto fail;

    av_opt_set_int(s, "uch", 0, 0);
    return s;
fail:
    av_log(s, AV_LOG_ERROR, "Failed to set option\n");
    swr_free(&s);
    return NULL;
}