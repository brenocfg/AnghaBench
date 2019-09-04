#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  enum AVCodecID { ____Placeholder_AVCodecID } AVCodecID ;
struct TYPE_7__ {scalar_t__ data; } ;
struct TYPE_5__ {scalar_t__ data; scalar_t__ size; TYPE_4__* buf; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_1__ codec_priv; } ;
typedef  TYPE_2__ MatroskaTrack ;
typedef  int /*<<< orphan*/  AVCodecTag ;

/* Variables and functions */
 scalar_t__ AV_INPUT_BUFFER_PADDING_SIZE ; 
 int /*<<< orphan*/  AV_RL32 (scalar_t__) ; 
 int /*<<< orphan*/  AV_WB32 (scalar_t__,scalar_t__) ; 
 scalar_t__ MATROSKA_TRACK_TYPE_VIDEO ; 
 int av_buffer_realloc (TYPE_4__**,scalar_t__) ; 
 int ff_codec_get_id (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ff_codec_movaudio_tags ; 
 int /*<<< orphan*/ * ff_codec_movvideo_tags ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int get_qt_codec(MatroskaTrack *track, uint32_t *fourcc, enum AVCodecID *codec_id)
{
    const AVCodecTag *codec_tags;

    codec_tags = track->type == MATROSKA_TRACK_TYPE_VIDEO ?
            ff_codec_movvideo_tags : ff_codec_movaudio_tags;

    /* Normalize noncompliant private data that starts with the fourcc
     * by expanding/shifting the data by 4 bytes and storing the data
     * size at the start. */
    if (ff_codec_get_id(codec_tags, AV_RL32(track->codec_priv.data))) {
        int ret = av_buffer_realloc(&track->codec_priv.buf,
                                    track->codec_priv.size + 4 + AV_INPUT_BUFFER_PADDING_SIZE);
        if (ret < 0)
            return ret;

        track->codec_priv.data = track->codec_priv.buf->data;
        memmove(track->codec_priv.data + 4, track->codec_priv.data, track->codec_priv.size);
        track->codec_priv.size += 4;
        AV_WB32(track->codec_priv.data, track->codec_priv.size);
    }

    *fourcc = AV_RL32(track->codec_priv.data + 4);
    *codec_id = ff_codec_get_id(codec_tags, *fourcc);

    return 0;
}