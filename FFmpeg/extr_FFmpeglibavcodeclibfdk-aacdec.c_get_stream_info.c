#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_9__ {scalar_t__ sample_rate; int channel_layout; int channels; int /*<<< orphan*/  frame_size; TYPE_1__* priv_data; } ;
struct TYPE_8__ {scalar_t__ sampleRate; int numChannels; size_t* pChannelType; int /*<<< orphan*/  frameSize; } ;
struct TYPE_7__ {int /*<<< orphan*/  handle; } ;
typedef  TYPE_1__ FDKAACDecContext ;
typedef  TYPE_2__ CStreamInfo ;
typedef  TYPE_3__ AVCodecContext ;
typedef  size_t AUDIO_CHANNEL_TYPE ;

/* Variables and functions */
 size_t ACT_BACK ; 
 size_t ACT_BACK_TOP ; 
 size_t ACT_FRONT ; 
 size_t ACT_FRONT_TOP ; 
 size_t ACT_LFE ; 
 size_t ACT_NONE ; 
 size_t ACT_SIDE ; 
 size_t ACT_SIDE_TOP ; 
 size_t ACT_TOP ; 
 int AVERROR_UNKNOWN ; 
 int AV_CH_BACK_CENTER ; 
 int AV_CH_BACK_LEFT ; 
 int AV_CH_BACK_RIGHT ; 
 int AV_CH_FRONT_CENTER ; 
 int AV_CH_FRONT_LEFT_OF_CENTER ; 
 int AV_CH_FRONT_RIGHT_OF_CENTER ; 
 int AV_CH_LAYOUT_STEREO ; 
 int AV_CH_LOW_FREQUENCY ; 
 int AV_CH_SIDE_LEFT ; 
 int AV_CH_SIDE_RIGHT ; 
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 size_t FF_ARRAY_ELEMS (int*) ; 
 TYPE_2__* aacDecoder_GetStreamInfo (int /*<<< orphan*/ ) ; 
 int av_get_channel_layout_nb_channels (int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,...) ; 

__attribute__((used)) static int get_stream_info(AVCodecContext *avctx)
{
    FDKAACDecContext *s   = avctx->priv_data;
    CStreamInfo *info     = aacDecoder_GetStreamInfo(s->handle);
    int channel_counts[0x24] = { 0 };
    int i, ch_error       = 0;
    uint64_t ch_layout    = 0;

    if (!info) {
        av_log(avctx, AV_LOG_ERROR, "Unable to get stream info\n");
        return AVERROR_UNKNOWN;
    }

    if (info->sampleRate <= 0) {
        av_log(avctx, AV_LOG_ERROR, "Stream info not initialized\n");
        return AVERROR_UNKNOWN;
    }
    avctx->sample_rate = info->sampleRate;
    avctx->frame_size  = info->frameSize;

    for (i = 0; i < info->numChannels; i++) {
        AUDIO_CHANNEL_TYPE ctype = info->pChannelType[i];
        if (ctype <= ACT_NONE || ctype >= FF_ARRAY_ELEMS(channel_counts)) {
            av_log(avctx, AV_LOG_WARNING, "unknown channel type\n");
            break;
        }
        channel_counts[ctype]++;
    }
    av_log(avctx, AV_LOG_DEBUG,
           "%d channels - front:%d side:%d back:%d lfe:%d top:%d\n",
           info->numChannels,
           channel_counts[ACT_FRONT], channel_counts[ACT_SIDE],
           channel_counts[ACT_BACK],  channel_counts[ACT_LFE],
           channel_counts[ACT_FRONT_TOP] + channel_counts[ACT_SIDE_TOP] +
           channel_counts[ACT_BACK_TOP]  + channel_counts[ACT_TOP]);

    switch (channel_counts[ACT_FRONT]) {
    case 4:
        ch_layout |= AV_CH_LAYOUT_STEREO | AV_CH_FRONT_LEFT_OF_CENTER |
                     AV_CH_FRONT_RIGHT_OF_CENTER;
        break;
    case 3:
        ch_layout |= AV_CH_LAYOUT_STEREO | AV_CH_FRONT_CENTER;
        break;
    case 2:
        ch_layout |= AV_CH_LAYOUT_STEREO;
        break;
    case 1:
        ch_layout |= AV_CH_FRONT_CENTER;
        break;
    default:
        av_log(avctx, AV_LOG_WARNING,
               "unsupported number of front channels: %d\n",
               channel_counts[ACT_FRONT]);
        ch_error = 1;
        break;
    }
    if (channel_counts[ACT_SIDE] > 0) {
        if (channel_counts[ACT_SIDE] == 2) {
            ch_layout |= AV_CH_SIDE_LEFT | AV_CH_SIDE_RIGHT;
        } else {
            av_log(avctx, AV_LOG_WARNING,
                   "unsupported number of side channels: %d\n",
                   channel_counts[ACT_SIDE]);
            ch_error = 1;
        }
    }
    if (channel_counts[ACT_BACK] > 0) {
        switch (channel_counts[ACT_BACK]) {
        case 3:
            ch_layout |= AV_CH_BACK_LEFT | AV_CH_BACK_RIGHT | AV_CH_BACK_CENTER;
            break;
        case 2:
            ch_layout |= AV_CH_BACK_LEFT | AV_CH_BACK_RIGHT;
            break;
        case 1:
            ch_layout |= AV_CH_BACK_CENTER;
            break;
        default:
            av_log(avctx, AV_LOG_WARNING,
                   "unsupported number of back channels: %d\n",
                   channel_counts[ACT_BACK]);
            ch_error = 1;
            break;
        }
    }
    if (channel_counts[ACT_LFE] > 0) {
        if (channel_counts[ACT_LFE] == 1) {
            ch_layout |= AV_CH_LOW_FREQUENCY;
        } else {
            av_log(avctx, AV_LOG_WARNING,
                   "unsupported number of LFE channels: %d\n",
                   channel_counts[ACT_LFE]);
            ch_error = 1;
        }
    }
    if (!ch_error &&
        av_get_channel_layout_nb_channels(ch_layout) != info->numChannels) {
        av_log(avctx, AV_LOG_WARNING, "unsupported channel configuration\n");
        ch_error = 1;
    }
    if (ch_error)
        avctx->channel_layout = 0;
    else
        avctx->channel_layout = ch_layout;

    avctx->channels = info->numChannels;

    return 0;
}