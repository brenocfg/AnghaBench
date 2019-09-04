#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_8__ {int /*<<< orphan*/  const* subtitle_codec; int /*<<< orphan*/  const* audio_codec; int /*<<< orphan*/  const* video_codec; } ;
struct TYPE_7__ {TYPE_1__* codecpar; } ;
struct TYPE_6__ {int codec_type; } ;
typedef  TYPE_2__ AVStream ;
typedef  TYPE_3__ AVFormatContext ;
typedef  int /*<<< orphan*/  AVCodec ;

/* Variables and functions */
#define  AVMEDIA_TYPE_AUDIO 130 
#define  AVMEDIA_TYPE_SUBTITLE 129 
#define  AVMEDIA_TYPE_VIDEO 128 
 int /*<<< orphan*/  const* avcodec_find_decoder (int) ; 

__attribute__((used)) static const AVCodec *find_decoder(AVFormatContext *s, const AVStream *st, enum AVCodecID codec_id)
{
#if FF_API_LAVF_AVCTX
FF_DISABLE_DEPRECATION_WARNINGS
    if (st->codec->codec)
        return st->codec->codec;
FF_ENABLE_DEPRECATION_WARNINGS
#endif

    switch (st->codecpar->codec_type) {
    case AVMEDIA_TYPE_VIDEO:
        if (s->video_codec)    return s->video_codec;
        break;
    case AVMEDIA_TYPE_AUDIO:
        if (s->audio_codec)    return s->audio_codec;
        break;
    case AVMEDIA_TYPE_SUBTITLE:
        if (s->subtitle_codec) return s->subtitle_codec;
        break;
    }

    return avcodec_find_decoder(codec_id);
}