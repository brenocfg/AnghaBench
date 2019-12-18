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
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int int8_t ;
typedef  int int64_t ;
struct TYPE_16__ {TYPE_4__** streams; TYPE_3__* priv_data; int /*<<< orphan*/ * pb; } ;
struct TYPE_15__ {int /*<<< orphan*/  time_base; TYPE_1__* codecpar; } ;
struct TYPE_14__ {int packet_count; int audio_index; int video_index; TYPE_2__* start; } ;
struct TYPE_13__ {struct TYPE_13__* next; } ;
struct TYPE_12__ {int codec_id; scalar_t__ format; int height; int width; int channels; int bits_per_coded_sample; int /*<<< orphan*/  sample_rate; } ;
typedef  TYPE_2__ FILMPacket ;
typedef  TYPE_3__ FILMOutputContext ;
typedef  TYPE_4__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
#define  AV_CODEC_ID_CINEPAK 129 
#define  AV_CODEC_ID_RAWVIDEO 128 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 scalar_t__ AV_PIX_FMT_RGB24 ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int /*<<< orphan*/  av_inv_q (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*) ; 
 int av_q2d (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_w8 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avio_wb16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_wb32 (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ffio_wfourcc (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  film_write_packet_to_header (TYPE_5__*,TYPE_2__*) ; 
 int get_audio_codec_id (int) ; 
 int shift_data (TYPE_5__*,int) ; 

__attribute__((used)) static int film_write_header(AVFormatContext *format_context)
{
    int ret = 0;
    int64_t sample_table_size, stabsize, headersize;
    int8_t audio_codec;
    AVIOContext *pb = format_context->pb;
    FILMOutputContext *film = format_context->priv_data;
    FILMPacket *prev, *packet;
    AVStream *audio = NULL;
    AVStream *video = NULL;

    /* Calculate how much we need to reserve for the header;
     * this is the amount the rest of the data will be shifted up by. */
    sample_table_size = film->packet_count * 16;
    stabsize = 16 + sample_table_size;
    headersize = 16 + /* FILM header base */
                 32 + /* FDSC chunk */
                 stabsize;

    ret = shift_data(format_context, headersize);
    if (ret < 0)
        return ret;
    /* Seek back to the beginning to start writing the header now */
    avio_seek(pb, 0, SEEK_SET);

    if (film->audio_index > -1)
        audio = format_context->streams[film->audio_index];
    if (film->video_index > -1)
        video = format_context->streams[film->video_index];

    if (audio != NULL) {
        audio_codec = get_audio_codec_id(audio->codecpar->codec_id);
        if (audio_codec < 0) {
            av_log(format_context, AV_LOG_ERROR, "Incompatible audio stream format.\n");
            return AVERROR(EINVAL);
        }
    }

    if (video->codecpar->format != AV_PIX_FMT_RGB24) {
        av_log(format_context, AV_LOG_ERROR, "Pixel format must be rgb24.\n");
        return AVERROR(EINVAL);
    }

    /* First, write the FILM header; this is very simple */

    ffio_wfourcc(pb, "FILM");
    avio_wb32(pb, 48 + stabsize);
    /* This seems to be okay to hardcode, since this muxer targets 1.09 features;
     * videos produced by this muxer are readable by 1.08 and lower players. */
    ffio_wfourcc(pb, "1.09");
    /* I have no idea what this field does, might be reserved */
    avio_wb32(pb, 0);

    /* Next write the FDSC (file description) chunk */
    ffio_wfourcc(pb, "FDSC");
    avio_wb32(pb, 0x20); /* Size of FDSC chunk */

    /* The only two supported codecs; raw video is rare */
    switch (video->codecpar->codec_id) {
    case AV_CODEC_ID_CINEPAK:
        ffio_wfourcc(pb, "cvid");
        break;
    case AV_CODEC_ID_RAWVIDEO:
        ffio_wfourcc(pb, "raw ");
        break;
    default:
        av_log(format_context, AV_LOG_ERROR, "Incompatible video stream format.\n");
        return AVERROR(EINVAL);
    }

    avio_wb32(pb, video->codecpar->height);
    avio_wb32(pb, video->codecpar->width);
    avio_w8(pb, 24); /* Bits per pixel - observed to always be 24 */

    if (audio != NULL) {
        avio_w8(pb, audio->codecpar->channels); /* Audio channels */
        avio_w8(pb, audio->codecpar->bits_per_coded_sample); /* Audio bit depth */
        avio_w8(pb, audio_codec); /* Compression - 0 is PCM, 2 is ADX */
        avio_wb16(pb, audio->codecpar->sample_rate); /* Audio sampling rate */
    } else {
        /* Set all these fields to 0 if there's no audio */
        avio_w8(pb, 0);
        avio_w8(pb, 0);
        avio_w8(pb, 0);
        avio_wb16(pb, 0);
    }

    /* I have no idea what this pair of fields does either, might be reserved */
    avio_wb32(pb, 0);
    avio_wb16(pb, 0);

    /* Finally, write the STAB (sample table) chunk */
    ffio_wfourcc(pb, "STAB");
    avio_wb32(pb, 16 + (film->packet_count * 16));
    /* Framerate base frequency. Here we're assuming that the frame rate is even.
     * In real world Sega FILM files, there are usually a couple of approaches:
     * a) framerate base frequency is the same as the framerate, and ticks
     *    increment by 1 every frame, or
     * b) framerate base frequency is a much larger number, and ticks
     *    increment by larger steps every frame.
     * The latter occurs even in cases where the frame rate is even; for example, in
     * Lunar: Silver Star Story, the base frequency is 600 and each frame, the ticks
     * are incremented by 25 for an evenly spaced framerate of 24fps. */
    avio_wb32(pb, av_q2d(av_inv_q(video->time_base)));

    avio_wb32(pb, film->packet_count);

    avio_flush(pb);

    /* Finally, write out each packet's data to the header */
    packet = film->start;
    while (packet != NULL) {
        film_write_packet_to_header(format_context, packet);
        prev = packet;
        packet = packet->next;
        av_freep(&prev);
    }

    return 0;
}