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
struct TYPE_4__ {scalar_t__ sample_rate; int /*<<< orphan*/  sample_fmt; int /*<<< orphan*/  channels; } ;
typedef  int /*<<< orphan*/  SwrContext ;
typedef  TYPE_1__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_assert0 (int) ; 
 int /*<<< orphan*/  av_get_default_channel_layout (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/ * swr_alloc_set_opts (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  swr_free (int /*<<< orphan*/ **) ; 
 int swr_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int init_resampler(AVCodecContext *input_codec_context,
                          AVCodecContext *output_codec_context,
                          SwrContext **resample_context)
{
        int error;

        /*
         * Create a resampler context for the conversion.
         * Set the conversion parameters.
         * Default channel layouts based on the number of channels
         * are assumed for simplicity (they are sometimes not detected
         * properly by the demuxer and/or decoder).
         */
        *resample_context = swr_alloc_set_opts(NULL,
                                              av_get_default_channel_layout(output_codec_context->channels),
                                              output_codec_context->sample_fmt,
                                              output_codec_context->sample_rate,
                                              av_get_default_channel_layout(input_codec_context->channels),
                                              input_codec_context->sample_fmt,
                                              input_codec_context->sample_rate,
                                              0, NULL);
        if (!*resample_context) {
            fprintf(stderr, "Could not allocate resample context\n");
            return AVERROR(ENOMEM);
        }
        /*
        * Perform a sanity check so that the number of converted samples is
        * not greater than the number of samples to be converted.
        * If the sample rates differ, this case has to be handled differently
        */
        av_assert0(output_codec_context->sample_rate == input_codec_context->sample_rate);

        /* Open the resampler with the specified parameters. */
        if ((error = swr_init(*resample_context)) < 0) {
            fprintf(stderr, "Could not open resample context\n");
            swr_free(resample_context);
            return error;
        }
    return 0;
}