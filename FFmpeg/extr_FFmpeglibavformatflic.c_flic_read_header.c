#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int width; int height; int block_align; int sample_rate; int channels; int bit_rate; int bits_per_coded_sample; int /*<<< orphan*/  extradata; scalar_t__ extradata_size; int /*<<< orphan*/  channel_layout; scalar_t__ codec_tag; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_12__ {int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_11__ {TYPE_5__* codecpar; int /*<<< orphan*/  index; } ;
struct TYPE_10__ {int /*<<< orphan*/  audio_stream_index; int /*<<< orphan*/  video_stream_index; scalar_t__ frame_number; } ;
typedef  TYPE_1__ FlicDemuxContext ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CODEC_ID_FLIC ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_U8 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 void* AV_RL16 (unsigned char*) ; 
 void* AV_RL32 (unsigned char*) ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 void* FLIC_CHUNK_MAGIC_1 ; 
 int FLIC_DEFAULT_SPEED ; 
 int FLIC_FILE_MAGIC_1 ; 
 int FLIC_FILE_MAGIC_2 ; 
 int FLIC_FILE_MAGIC_3 ; 
 int FLIC_HEADER_SIZE ; 
 int FLIC_MC_SPEED ; 
 int FLIC_PREAMBLE_SIZE ; 
 void* FLIC_TFTD_CHUNK_AUDIO ; 
 int FLIC_TFTD_SAMPLE_RATE ; 
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*) ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 
 scalar_t__ ff_alloc_extradata (TYPE_5__*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,unsigned char*,int) ; 

__attribute__((used)) static int flic_read_header(AVFormatContext *s)
{
    FlicDemuxContext *flic = s->priv_data;
    AVIOContext *pb = s->pb;
    unsigned char header[FLIC_HEADER_SIZE];
    AVStream *st, *ast;
    int speed;
    int magic_number;
    unsigned char preamble[FLIC_PREAMBLE_SIZE];

    flic->frame_number = 0;

    /* load the whole header and pull out the width and height */
    if (avio_read(pb, header, FLIC_HEADER_SIZE) != FLIC_HEADER_SIZE)
        return AVERROR(EIO);

    magic_number = AV_RL16(&header[4]);
    speed = AV_RL32(&header[0x10]);
    if (speed == 0)
        speed = FLIC_DEFAULT_SPEED;

    /* initialize the decoder streams */
    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);
    flic->video_stream_index = st->index;
    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id = AV_CODEC_ID_FLIC;
    st->codecpar->codec_tag = 0;  /* no fourcc */
    st->codecpar->width = AV_RL16(&header[0x08]);
    st->codecpar->height = AV_RL16(&header[0x0A]);

    if (!st->codecpar->width || !st->codecpar->height) {
        /* Ugly hack needed for the following sample: */
        /* http://samples.mplayerhq.hu/fli-flc/fli-bugs/specular.flc */
        av_log(s, AV_LOG_WARNING,
               "File with no specified width/height. Trying 640x480.\n");
        st->codecpar->width  = 640;
        st->codecpar->height = 480;
    }

    /* send over the whole 128-byte FLIC header */
    if (ff_alloc_extradata(st->codecpar, FLIC_HEADER_SIZE))
        return AVERROR(ENOMEM);
    memcpy(st->codecpar->extradata, header, FLIC_HEADER_SIZE);

    /* peek at the preamble to detect TFTD videos - they seem to always start with an audio chunk */
    if (avio_read(pb, preamble, FLIC_PREAMBLE_SIZE) != FLIC_PREAMBLE_SIZE) {
        av_log(s, AV_LOG_ERROR, "Failed to peek at preamble\n");
        return AVERROR(EIO);
    }

    avio_seek(pb, -FLIC_PREAMBLE_SIZE, SEEK_CUR);

    /* Time to figure out the framerate:
     * If the first preamble's magic number is 0xAAAA then this file is from
     * X-COM: Terror from the Deep. If on the other hand there is a FLIC chunk
     * magic number at offset 0x10 assume this file is from Magic Carpet instead.
     * If neither of the above is true then this is a normal FLIC file.
     */
    if (AV_RL16(&preamble[4]) == FLIC_TFTD_CHUNK_AUDIO) {
        /* TFTD videos have an extra 22050 Hz 8-bit mono audio stream */
        ast = avformat_new_stream(s, NULL);
        if (!ast)
            return AVERROR(ENOMEM);

        flic->audio_stream_index = ast->index;

        /* all audio frames are the same size, so use the size of the first chunk for block_align */
        ast->codecpar->block_align = AV_RL32(&preamble[0]);
        ast->codecpar->codec_type = AVMEDIA_TYPE_AUDIO;
        ast->codecpar->codec_id = AV_CODEC_ID_PCM_U8;
        ast->codecpar->codec_tag = 0;
        ast->codecpar->sample_rate = FLIC_TFTD_SAMPLE_RATE;
        ast->codecpar->channels = 1;
        ast->codecpar->bit_rate = st->codecpar->sample_rate * 8;
        ast->codecpar->bits_per_coded_sample = 8;
        ast->codecpar->channel_layout = AV_CH_LAYOUT_MONO;
        ast->codecpar->extradata_size = 0;

        /* Since the header information is incorrect we have to figure out the
         * framerate using block_align and the fact that the audio is 22050 Hz.
         * We usually have two cases: 2205 -> 10 fps and 1470 -> 15 fps */
        avpriv_set_pts_info(st, 64, ast->codecpar->block_align, FLIC_TFTD_SAMPLE_RATE);
        avpriv_set_pts_info(ast, 64, 1, FLIC_TFTD_SAMPLE_RATE);
    } else if (AV_RL16(&header[0x10]) == FLIC_CHUNK_MAGIC_1) {
        avpriv_set_pts_info(st, 64, FLIC_MC_SPEED, 70);

        /* rewind the stream since the first chunk is at offset 12 */
        avio_seek(pb, 12, SEEK_SET);

        /* send over abbreviated FLIC header chunk */
        av_freep(&st->codecpar->extradata);
        if (ff_alloc_extradata(st->codecpar, 12))
            return AVERROR(ENOMEM);
        memcpy(st->codecpar->extradata, header, 12);

    } else if (magic_number == FLIC_FILE_MAGIC_1) {
        avpriv_set_pts_info(st, 64, speed, 70);
    } else if ((magic_number == FLIC_FILE_MAGIC_2) ||
               (magic_number == FLIC_FILE_MAGIC_3)) {
        avpriv_set_pts_info(st, 64, speed, 1000);
    } else {
        av_log(s, AV_LOG_ERROR, "Invalid or unsupported magic chunk in file\n");
        return AVERROR_INVALIDDATA;
    }

    return 0;
}