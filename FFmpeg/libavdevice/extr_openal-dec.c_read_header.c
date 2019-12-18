#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_15__ {int sample_size; int channels; int sample_step; scalar_t__ device; TYPE_5__ sample_format; int /*<<< orphan*/  sample_rate; scalar_t__ list_devices; } ;
typedef  TYPE_1__ al_data ;
struct TYPE_20__ {int channels; int /*<<< orphan*/  codec_id; } ;
struct TYPE_18__ {int channels; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  codec_type; } ;
struct TYPE_17__ {scalar_t__* url; TYPE_1__* priv_data; } ;
struct TYPE_16__ {TYPE_4__* codecpar; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;
typedef  TYPE_4__ AVCodecParameters ;
typedef  TYPE_5__ ALCenum ;

/* Variables and functions */
#define  AL_FORMAT_MONO16 131 
#define  AL_FORMAT_MONO8 130 
#define  AL_FORMAT_STEREO16 129 
#define  AL_FORMAT_STEREO8 128 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EXIT ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int al_get_error (scalar_t__,char const**) ; 
 int /*<<< orphan*/  alcCaptureCloseDevice (scalar_t__) ; 
 scalar_t__ alcCaptureOpenDevice (scalar_t__*,int /*<<< orphan*/ ,TYPE_5__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alcCaptureStart (scalar_t__) ; 
 int av_get_bits_per_sample (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,char const*) ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 
 TYPE_8__* get_al_format_info (TYPE_5__) ; 
 int /*<<< orphan*/  print_al_capture_devices (TYPE_3__*) ; 

__attribute__((used)) static int read_header(AVFormatContext *ctx)
{
    al_data *ad = ctx->priv_data;
    static const ALCenum sample_formats[2][2] = {
        { AL_FORMAT_MONO8,  AL_FORMAT_STEREO8  },
        { AL_FORMAT_MONO16, AL_FORMAT_STEREO16 }
    };
    int error = 0;
    const char *error_msg;
    AVStream *st = NULL;
    AVCodecParameters *par = NULL;

    if (ad->list_devices) {
        print_al_capture_devices(ctx);
        return AVERROR_EXIT;
    }

    ad->sample_format = sample_formats[ad->sample_size/8-1][ad->channels-1];

    /* Open device for capture */
    ad->device =
        alcCaptureOpenDevice(ctx->url[0] ? ctx->url : NULL,
                             ad->sample_rate,
                             ad->sample_format,
                             ad->sample_rate); /* Maximum 1 second of sample data to be read at once */

    if (error = al_get_error(ad->device, &error_msg)) goto fail;

    /* Create stream */
    if (!(st = avformat_new_stream(ctx, NULL))) {
        error = AVERROR(ENOMEM);
        goto fail;
    }

    /* We work in microseconds */
    avpriv_set_pts_info(st, 64, 1, 1000000);

    /* Set codec parameters */
    par = st->codecpar;
    par->codec_type = AVMEDIA_TYPE_AUDIO;
    par->sample_rate = ad->sample_rate;
    par->channels = get_al_format_info(ad->sample_format)->channels;
    par->codec_id = get_al_format_info(ad->sample_format)->codec_id;

    /* This is needed to read the audio data */
    ad->sample_step = (av_get_bits_per_sample(get_al_format_info(ad->sample_format)->codec_id) *
                       get_al_format_info(ad->sample_format)->channels) / 8;

    /* Finally, start the capture process */
    alcCaptureStart(ad->device);

    return 0;

fail:
    /* Handle failure */
    if (ad->device)
        alcCaptureCloseDevice(ad->device);
    if (error_msg)
        av_log(ctx, AV_LOG_ERROR, "Cannot open device: %s\n", error_msg);
    return error;
}