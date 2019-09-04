#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint8_t ;
typedef  int uint32_t ;
struct TYPE_11__ {int audio_stream_index; void* bps; void* channels; void* sample_rate; void* version; int /*<<< orphan*/  video_stream_index; } ;
typedef  TYPE_1__ WsVqaDemuxContext ;
struct TYPE_14__ {void** extradata; void* height; void* width; scalar_t__ codec_tag; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
struct TYPE_13__ {int /*<<< orphan*/  ctx_flags; int /*<<< orphan*/ * pb; TYPE_1__* priv_data; } ;
struct TYPE_12__ {void* duration; void* nb_frames; TYPE_6__* codecpar; int /*<<< orphan*/  index; scalar_t__ start_time; } ;
typedef  TYPE_2__ AVStream ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_3__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVFMTCTX_NOHEADER ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CODEC_ID_WS_VQA ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_RB32 (void**) ; 
 void* AV_RL16 (void**) ; 
#define  CIND_TAG 135 
#define  CINF_TAG 134 
#define  CINH_TAG 133 
#define  CMDS_TAG 132 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
#define  FINF_TAG 131 
#define  PIND_TAG 130 
#define  PINF_TAG 129 
#define  PINH_TAG 128 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  VQA_HEADER_SIZE ; 
 int VQA_PREAMBLE_SIZE ; 
 int av_fourcc2str (int) ; 
 int /*<<< orphan*/  av_log (TYPE_3__*,int /*<<< orphan*/ ,char*,int) ; 
 TYPE_2__* avformat_new_stream (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,void**,int) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_2__*,int,int,int) ; 
 scalar_t__ ff_get_extradata (TYPE_3__*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wsvqa_read_header(AVFormatContext *s)
{
    WsVqaDemuxContext *wsvqa = s->priv_data;
    AVIOContext *pb = s->pb;
    AVStream *st;
    uint8_t *header;
    uint8_t scratch[VQA_PREAMBLE_SIZE];
    uint32_t chunk_tag;
    uint32_t chunk_size;
    int fps;

    /* initialize the video decoder stream */
    st = avformat_new_stream(s, NULL);
    if (!st)
        return AVERROR(ENOMEM);
    st->start_time = 0;
    wsvqa->video_stream_index = st->index;
    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
    st->codecpar->codec_id = AV_CODEC_ID_WS_VQA;
    st->codecpar->codec_tag = 0;  /* no fourcc */

    /* skip to the start of the VQA header */
    avio_seek(pb, 20, SEEK_SET);

    /* the VQA header needs to go to the decoder */
    if (ff_get_extradata(s, st->codecpar, pb, VQA_HEADER_SIZE) < 0)
        return AVERROR(ENOMEM);
    header = st->codecpar->extradata;
    st->codecpar->width = AV_RL16(&header[6]);
    st->codecpar->height = AV_RL16(&header[8]);
    fps = header[12];
    st->nb_frames =
    st->duration  = AV_RL16(&header[4]);
    if (fps < 1 || fps > 30) {
        av_log(s, AV_LOG_ERROR, "invalid fps: %d\n", fps);
        return AVERROR_INVALIDDATA;
    }
    avpriv_set_pts_info(st, 64, 1, fps);

    wsvqa->version      = AV_RL16(&header[ 0]);
    wsvqa->sample_rate  = AV_RL16(&header[24]);
    wsvqa->channels     = header[26];
    wsvqa->bps          = header[27];
    wsvqa->audio_stream_index = -1;

    s->ctx_flags |= AVFMTCTX_NOHEADER;

    /* there are 0 or more chunks before the FINF chunk; iterate until
     * FINF has been skipped and the file will be ready to be demuxed */
    do {
        if (avio_read(pb, scratch, VQA_PREAMBLE_SIZE) != VQA_PREAMBLE_SIZE)
            return AVERROR(EIO);
        chunk_tag = AV_RB32(&scratch[0]);
        chunk_size = AV_RB32(&scratch[4]);

        /* catch any unknown header tags, for curiosity */
        switch (chunk_tag) {
        case CINF_TAG:
        case CINH_TAG:
        case CIND_TAG:
        case PINF_TAG:
        case PINH_TAG:
        case PIND_TAG:
        case FINF_TAG:
        case CMDS_TAG:
            break;

        default:
            av_log(s, AV_LOG_ERROR, " note: unknown chunk seen (%s)\n",
                   av_fourcc2str(chunk_tag));
            break;
        }

        avio_skip(pb, chunk_size);
    } while (chunk_tag != FINF_TAG);

    return 0;
}