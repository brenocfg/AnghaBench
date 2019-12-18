#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_8__ {int capabilities; int id; } ;
typedef  int /*<<< orphan*/  AVStream ;
typedef  int /*<<< orphan*/  AVFormatContext ;
typedef  TYPE_1__ AVCodec ;

/* Variables and functions */
 int AV_CODEC_CAP_AVOID_PROBING ; 
 int AV_CODEC_CAP_EXPERIMENTAL ; 
 int AV_CODEC_ID_H264 ; 
 scalar_t__ av_codec_is_decoder (TYPE_1__ const*) ; 
 TYPE_1__* av_codec_next (TYPE_1__ const*) ; 
 TYPE_1__ const* avcodec_find_decoder_by_name (char*) ; 
 TYPE_1__* find_decoder (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static const AVCodec *find_probe_decoder(AVFormatContext *s, const AVStream *st, enum AVCodecID codec_id)
{
    const AVCodec *codec;

#if CONFIG_H264_DECODER
    /* Other parts of the code assume this decoder to be used for h264,
     * so force it if possible. */
    if (codec_id == AV_CODEC_ID_H264)
        return avcodec_find_decoder_by_name("h264");
#endif

    codec = find_decoder(s, st, codec_id);
    if (!codec)
        return NULL;

    if (codec->capabilities & AV_CODEC_CAP_AVOID_PROBING) {
        const AVCodec *probe_codec = NULL;
        while (probe_codec = av_codec_next(probe_codec)) {
            if (probe_codec->id == codec_id &&
                    av_codec_is_decoder(probe_codec) &&
                    !(probe_codec->capabilities & (AV_CODEC_CAP_AVOID_PROBING | AV_CODEC_CAP_EXPERIMENTAL))) {
                return probe_codec;
            }
        }
    }

    return codec;
}