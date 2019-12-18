#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ sample_fmt; scalar_t__ sample_rate; scalar_t__ channel_layout; scalar_t__ lfe_mix_level; scalar_t__ center_mix_level; scalar_t__ surround_mix_level; } ;
struct TYPE_7__ {scalar_t__ sample_fmt; scalar_t__ sample_rate; scalar_t__ channel_layout; scalar_t__ lfe_mix_level; scalar_t__ center_mix_level; scalar_t__ surround_mix_level; int /*<<< orphan*/  channels; } ;
struct TYPE_6__ {scalar_t__ sample_fmt; scalar_t__ sample_rate; scalar_t__ channel_layout; scalar_t__ matrix_encoding; scalar_t__ maxval; } ;
struct TYPE_9__ {int resample_needed; TYPE_3__ in; TYPE_2__ resample; int /*<<< orphan*/ * swresample; TYPE_1__ out; } ;
typedef  TYPE_4__ hb_audio_resample_t ;

/* Variables and functions */
 int /*<<< orphan*/  av_get_channel_layout_nb_channels (scalar_t__) ; 
 int /*<<< orphan*/  av_opt_set_double (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_opt_set_int (int /*<<< orphan*/ *,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_strerror (int,char*,int) ; 
 int /*<<< orphan*/  hb_error (char*,...) ; 
 int /*<<< orphan*/ * swr_alloc () ; 
 int /*<<< orphan*/  swr_free (int /*<<< orphan*/ **) ; 
 int swr_init (int /*<<< orphan*/ *) ; 

int hb_audio_resample_update(hb_audio_resample_t *resample)
{
    if (resample == NULL)
    {
        hb_error("hb_audio_resample_update: resample is NULL");
        return 1;
    }

    int ret, resample_changed;

    resample->resample_needed =
        (resample->out.sample_fmt != resample->in.sample_fmt ||
         resample->out.sample_rate != resample->in.sample_rate ||
         resample->out.channel_layout != resample->in.channel_layout);

    resample_changed =
        (resample->resample_needed &&
         (resample->resample.sample_fmt != resample->in.sample_fmt ||
          resample->resample.sample_rate != resample->in.sample_rate ||
          resample->resample.channel_layout != resample->in.channel_layout ||
          resample->resample.lfe_mix_level != resample->in.lfe_mix_level ||
          resample->resample.center_mix_level != resample->in.center_mix_level ||
          resample->resample.surround_mix_level != resample->in.surround_mix_level));

    if (resample_changed || (resample->resample_needed &&
                             resample->swresample == NULL))
    {
        if (resample->swresample == NULL)
        {
            resample->swresample = swr_alloc();
            if (resample->swresample == NULL)
            {
                hb_error("hb_audio_resample_update: swr_alloc() failed");
                return 1;
            }

            av_opt_set_int(resample->swresample, "out_sample_fmt",
                           resample->out.sample_fmt, 0);
            av_opt_set_int(resample->swresample, "out_sample_rate",
                           resample->out.sample_rate, 0);
            av_opt_set_int(resample->swresample, "out_channel_layout",
                           resample->out.channel_layout, 0);
            av_opt_set_int(resample->swresample, "matrix_encoding",
                           resample->out.matrix_encoding, 0);
            av_opt_set_double(resample->swresample, "rematrix_maxval",
                              resample->out.maxval, 0);
        }

        av_opt_set_int(resample->swresample, "in_sample_fmt",
                       resample->in.sample_fmt, 0);
        av_opt_set_int(resample->swresample, "in_sample_rate",
                       resample->in.sample_rate, 0);
        av_opt_set_int(resample->swresample, "in_channel_layout",
                       resample->in.channel_layout, 0);
        av_opt_set_double(resample->swresample, "lfe_mix_level",
                          resample->in.lfe_mix_level, 0);
        av_opt_set_double(resample->swresample, "center_mix_level",
                          resample->in.center_mix_level, 0);
        av_opt_set_double(resample->swresample, "surround_mix_level",
                          resample->in.surround_mix_level, 0);

        if ((ret = swr_init(resample->swresample)))
        {
            char err_desc[64];
            av_strerror(ret, err_desc, 63);
            hb_error("hb_audio_resample_update: swr_init() failed (%s)",
                     err_desc);
            // swresample won't open, start over
            swr_free(&resample->swresample);
            return ret;
        }

        resample->resample.sample_fmt         = resample->in.sample_fmt;
        resample->resample.sample_rate        = resample->in.sample_rate;
        resample->resample.channel_layout     = resample->in.channel_layout;
        resample->resample.channels           =
            av_get_channel_layout_nb_channels(resample->in.channel_layout);
        resample->resample.lfe_mix_level      = resample->in.lfe_mix_level;
        resample->resample.center_mix_level   = resample->in.center_mix_level;
        resample->resample.surround_mix_level = resample->in.surround_mix_level;
    }

    return 0;
}