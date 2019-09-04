#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int UInt32 ;
struct TYPE_17__ {int /*<<< orphan*/  available; } ;
struct TYPE_16__ {int /*<<< orphan*/  used_frame_queue; int /*<<< orphan*/  encoding_frame; TYPE_8__ frame_queue; scalar_t__ eof; } ;
struct TYPE_15__ {int channels; int /*<<< orphan*/  sample_fmt; TYPE_5__* priv_data; } ;
struct TYPE_14__ {int nb_samples; int /*<<< orphan*/ * data; } ;
struct TYPE_13__ {int mNumberBuffers; TYPE_1__* mBuffers; } ;
struct TYPE_12__ {int mNumberChannels; int mDataByteSize; int /*<<< orphan*/  mData; } ;
typedef  int OSStatus ;
typedef  int /*<<< orphan*/  AudioStreamPacketDescription ;
typedef  int /*<<< orphan*/  AudioConverterRef ;
typedef  TYPE_2__ AudioBufferList ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;
typedef  TYPE_5__ ATDecodeContext ;

/* Variables and functions */
 int av_frame_ref (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  av_frame_unref (int /*<<< orphan*/ ) ; 
 int av_get_bytes_per_sample (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_bufqueue_add (TYPE_4__*,int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* ff_bufqueue_get (TYPE_8__*) ; 

__attribute__((used)) static OSStatus ffat_encode_callback(AudioConverterRef converter, UInt32 *nb_packets,
                                     AudioBufferList *data,
                                     AudioStreamPacketDescription **packets,
                                     void *inctx)
{
    AVCodecContext *avctx = inctx;
    ATDecodeContext *at = avctx->priv_data;
    AVFrame *frame;
    int ret;

    if (!at->frame_queue.available) {
        if (at->eof) {
            *nb_packets = 0;
            return 0;
        } else {
            *nb_packets = 0;
            return 1;
        }
    }

    frame = ff_bufqueue_get(&at->frame_queue);

    data->mNumberBuffers              = 1;
    data->mBuffers[0].mNumberChannels = avctx->channels;
    data->mBuffers[0].mDataByteSize   = frame->nb_samples *
                                        av_get_bytes_per_sample(avctx->sample_fmt) *
                                        avctx->channels;
    data->mBuffers[0].mData           = frame->data[0];
    if (*nb_packets > frame->nb_samples)
        *nb_packets = frame->nb_samples;

    av_frame_unref(at->encoding_frame);
    ret = av_frame_ref(at->encoding_frame, frame);
    if (ret < 0) {
        *nb_packets = 0;
        return ret;
    }

    ff_bufqueue_add(avctx, &at->used_frame_queue, frame);

    return 0;
}