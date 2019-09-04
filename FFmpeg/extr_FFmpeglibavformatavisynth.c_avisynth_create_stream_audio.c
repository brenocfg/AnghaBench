#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_3__* priv_data; } ;
struct TYPE_13__ {TYPE_1__* codecpar; int /*<<< orphan*/  duration; } ;
struct TYPE_12__ {int error; TYPE_2__* vi; } ;
struct TYPE_11__ {int sample_type; int /*<<< orphan*/  audio_samples_per_second; int /*<<< orphan*/  num_audio_samples; int /*<<< orphan*/  nchannels; } ;
struct TYPE_10__ {int /*<<< orphan*/  codec_id; int /*<<< orphan*/  channels; int /*<<< orphan*/  sample_rate; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_3__ AviSynthContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_UNKNOWN ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
#define  AVS_SAMPLE_FLOAT 132 
#define  AVS_SAMPLE_INT16 131 
#define  AVS_SAMPLE_INT24 130 
#define  AVS_SAMPLE_INT32 129 
#define  AVS_SAMPLE_INT8 128 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_F32LE ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S16LE ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S24LE ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_S32LE ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_U8 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_4__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int avisynth_create_stream_audio(AVFormatContext *s, AVStream *st)
{
    AviSynthContext *avs = s->priv_data;

    st->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
    st->codecpar->sample_rate = avs->vi->audio_samples_per_second;
    st->codecpar->channels    = avs->vi->nchannels;
    st->duration              = avs->vi->num_audio_samples;
    avpriv_set_pts_info(st, 64, 1, avs->vi->audio_samples_per_second);

    switch (avs->vi->sample_type) {
    case AVS_SAMPLE_INT8:
        st->codecpar->codec_id = AV_CODEC_ID_PCM_U8;
        break;
    case AVS_SAMPLE_INT16:
        st->codecpar->codec_id = AV_CODEC_ID_PCM_S16LE;
        break;
    case AVS_SAMPLE_INT24:
        st->codecpar->codec_id = AV_CODEC_ID_PCM_S24LE;
        break;
    case AVS_SAMPLE_INT32:
        st->codecpar->codec_id = AV_CODEC_ID_PCM_S32LE;
        break;
    case AVS_SAMPLE_FLOAT:
        st->codecpar->codec_id = AV_CODEC_ID_PCM_F32LE;
        break;
    default:
        av_log(s, AV_LOG_ERROR,
               "unknown AviSynth sample type %d\n", avs->vi->sample_type);
        avs->error = 1;
        return AVERROR_UNKNOWN;
    }
    return 0;
}