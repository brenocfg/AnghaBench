#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  format ;
typedef  int UInt32 ;
struct TYPE_16__ {int mChannelFlags; int /*<<< orphan*/  mChannelLabel; } ;
struct TYPE_15__ {int* channel_map; int /*<<< orphan*/  converter; } ;
struct TYPE_14__ {int channel_layout; int frame_size; int /*<<< orphan*/  channels; scalar_t__ sample_rate; TYPE_4__* priv_data; } ;
struct TYPE_13__ {int mFramesPerPacket; int mNumberChannelDescriptions; TYPE_5__* mChannelDescriptions; int /*<<< orphan*/  mChannelsPerFrame; scalar_t__ mSampleRate; } ;
typedef  TYPE_1__ AudioStreamBasicDescription ;
typedef  TYPE_1__ AudioChannelLayout ;
typedef  int /*<<< orphan*/  AudioChannelDescription ;
typedef  TYPE_3__ AVCodecContext ;
typedef  TYPE_4__ ATDecodeContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AudioConverterGetProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,TYPE_1__*) ; 
 int /*<<< orphan*/  AudioConverterGetPropertyInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  AudioConverterSetProperty (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_free (TYPE_1__*) ; 
 int av_get_default_channel_layout (int /*<<< orphan*/ ) ; 
 TYPE_1__* av_malloc (int) ; 
 int /*<<< orphan*/  ffat_compare_channel_descriptions ; 
 TYPE_1__* ffat_convert_layout (TYPE_1__*,int*) ; 
 int ffat_get_channel_id (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kAudioConverterCurrentInputStreamDescription ; 
 int /*<<< orphan*/  kAudioConverterCurrentOutputStreamDescription ; 
 int /*<<< orphan*/  kAudioConverterOutputChannelLayout ; 
 int /*<<< orphan*/  qsort (TYPE_5__*,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ffat_update_ctx(AVCodecContext *avctx)
{
    ATDecodeContext *at = avctx->priv_data;
    AudioStreamBasicDescription format;
    UInt32 size = sizeof(format);
    if (!AudioConverterGetProperty(at->converter,
                                   kAudioConverterCurrentInputStreamDescription,
                                   &size, &format)) {
        if (format.mSampleRate)
            avctx->sample_rate = format.mSampleRate;
        avctx->channels = format.mChannelsPerFrame;
        avctx->channel_layout = av_get_default_channel_layout(avctx->channels);
        avctx->frame_size = format.mFramesPerPacket;
    }

    if (!AudioConverterGetProperty(at->converter,
                                   kAudioConverterCurrentOutputStreamDescription,
                                   &size, &format)) {
        format.mSampleRate = avctx->sample_rate;
        format.mChannelsPerFrame = avctx->channels;
        AudioConverterSetProperty(at->converter,
                                  kAudioConverterCurrentOutputStreamDescription,
                                  size, &format);
    }

    if (!AudioConverterGetPropertyInfo(at->converter, kAudioConverterOutputChannelLayout,
                                       &size, NULL) && size) {
        AudioChannelLayout *layout = av_malloc(size);
        uint64_t layout_mask = 0;
        int i;
        if (!layout)
            return AVERROR(ENOMEM);
        AudioConverterGetProperty(at->converter, kAudioConverterOutputChannelLayout,
                                  &size, layout);
        if (!(layout = ffat_convert_layout(layout, &size)))
            return AVERROR(ENOMEM);
        for (i = 0; i < layout->mNumberChannelDescriptions; i++) {
            int id = ffat_get_channel_id(layout->mChannelDescriptions[i].mChannelLabel);
            if (id < 0)
                goto done;
            if (layout_mask & (1 << id))
                goto done;
            layout_mask |= 1 << id;
            layout->mChannelDescriptions[i].mChannelFlags = i; // Abusing flags as index
        }
        avctx->channel_layout = layout_mask;
        qsort(layout->mChannelDescriptions, layout->mNumberChannelDescriptions,
              sizeof(AudioChannelDescription), &ffat_compare_channel_descriptions);
        for (i = 0; i < layout->mNumberChannelDescriptions; i++)
            at->channel_map[i] = layout->mChannelDescriptions[i].mChannelFlags;
done:
        av_free(layout);
    }

    if (!avctx->frame_size)
        avctx->frame_size = 2048;

    return 0;
}