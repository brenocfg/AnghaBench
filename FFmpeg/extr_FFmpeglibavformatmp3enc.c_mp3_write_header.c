#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct AVFormatContext {int nb_streams; int /*<<< orphan*/  metadata_header_padding; int /*<<< orphan*/  pb; TYPE_3__** streams; TYPE_2__* priv_data; } ;
struct TYPE_6__ {TYPE_1__* codecpar; } ;
struct TYPE_5__ {int id3v2_version; int audio_stream_idx; int pics_to_write; int /*<<< orphan*/  id3; } ;
struct TYPE_4__ {scalar_t__ codec_type; scalar_t__ codec_id; } ;
typedef  TYPE_2__ MP3Context ;
typedef  TYPE_3__ AVStream ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_MP3 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ID3v2_DEFAULT_MAGIC ; 
 int /*<<< orphan*/  av_log (struct AVFormatContext*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ff_id3v2_finish (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ff_id3v2_start (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int ff_id3v2_write_metadata (struct AVFormatContext*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mp3_write_xing (struct AVFormatContext*) ; 

__attribute__((used)) static int mp3_write_header(struct AVFormatContext *s)
{
    MP3Context  *mp3 = s->priv_data;
    int ret, i;

    if (mp3->id3v2_version      &&
        mp3->id3v2_version != 3 &&
        mp3->id3v2_version != 4) {
        av_log(s, AV_LOG_ERROR, "Invalid ID3v2 version requested: %d. Only "
               "3, 4 or 0 (disabled) are allowed.\n", mp3->id3v2_version);
        return AVERROR(EINVAL);
    }

    /* check the streams -- we want exactly one audio and arbitrary number of
     * video (attached pictures) */
    mp3->audio_stream_idx = -1;
    for (i = 0; i < s->nb_streams; i++) {
        AVStream *st = s->streams[i];
        if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            if (mp3->audio_stream_idx >= 0 || st->codecpar->codec_id != AV_CODEC_ID_MP3) {
                av_log(s, AV_LOG_ERROR, "Invalid audio stream. Exactly one MP3 "
                       "audio stream is required.\n");
                return AVERROR(EINVAL);
            }
            mp3->audio_stream_idx = i;
        } else if (st->codecpar->codec_type != AVMEDIA_TYPE_VIDEO) {
            av_log(s, AV_LOG_ERROR, "Only audio streams and pictures are allowed in MP3.\n");
            return AVERROR(EINVAL);
        }
    }
    if (mp3->audio_stream_idx < 0) {
        av_log(s, AV_LOG_ERROR, "No audio stream present.\n");
        return AVERROR(EINVAL);
    }
    mp3->pics_to_write = s->nb_streams - 1;

    if (mp3->pics_to_write && !mp3->id3v2_version) {
        av_log(s, AV_LOG_ERROR, "Attached pictures were requested, but the "
               "ID3v2 header is disabled.\n");
        return AVERROR(EINVAL);
    }

    if (mp3->id3v2_version) {
        ff_id3v2_start(&mp3->id3, s->pb, mp3->id3v2_version, ID3v2_DEFAULT_MAGIC);
        ret = ff_id3v2_write_metadata(s, &mp3->id3);
        if (ret < 0)
            return ret;
    }

    if (!mp3->pics_to_write) {
        if (mp3->id3v2_version)
            ff_id3v2_finish(&mp3->id3, s->pb, s->metadata_header_padding);
        mp3_write_xing(s);
    }

    return 0;
}