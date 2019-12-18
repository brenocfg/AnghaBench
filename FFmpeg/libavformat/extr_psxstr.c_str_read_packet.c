#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_3__* priv_data; int /*<<< orphan*/ * pb; } ;
struct TYPE_19__ {int size; int pos; int duration; int /*<<< orphan*/  stream_index; int /*<<< orphan*/ * data; int /*<<< orphan*/ * buf; } ;
struct TYPE_18__ {int /*<<< orphan*/  start_time; TYPE_1__* codecpar; int /*<<< orphan*/  index; } ;
struct TYPE_17__ {TYPE_2__* channels; } ;
struct TYPE_16__ {int /*<<< orphan*/  audio_stream_index; int /*<<< orphan*/  video_stream_index; TYPE_5__ tmp_pkt; } ;
struct TYPE_15__ {int channels; int sample_rate; int block_align; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_tag; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; void* height; void* width; } ;
typedef  TYPE_3__ StrDemuxContext ;
typedef  TYPE_4__ AVStream ;
typedef  TYPE_5__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_STEREO ; 
 int /*<<< orphan*/  AV_CODEC_ID_ADPCM_XA ; 
 int /*<<< orphan*/  AV_CODEC_ID_MDEC ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 void* AV_RL16 (unsigned char*) ; 
 int AV_RL32 (unsigned char*) ; 
#define  CDXA_TYPE_AUDIO 130 
#define  CDXA_TYPE_DATA 129 
 unsigned char CDXA_TYPE_MASK ; 
#define  CDXA_TYPE_VIDEO 128 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
 int RAW_CD_SECTOR_SIZE ; 
 int VIDEO_DATA_CHUNK_SIZE ; 
 int /*<<< orphan*/  VIDEO_DATA_HEADER_SIZE ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_new_packet (TYPE_5__*,int) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_5__*) ; 
 TYPE_4__* avformat_new_stream (TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_read (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int avio_tell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_4__*,int,int,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int str_read_packet(AVFormatContext *s,
                           AVPacket *ret_pkt)
{
    AVIOContext *pb = s->pb;
    StrDemuxContext *str = s->priv_data;
    unsigned char sector[RAW_CD_SECTOR_SIZE];
    int channel;
    AVPacket *pkt;
    AVStream *st;

    while (1) {

        if (avio_read(pb, sector, RAW_CD_SECTOR_SIZE) != RAW_CD_SECTOR_SIZE)
            return AVERROR(EIO);

        channel = sector[0x11];
        if (channel >= 32)
            return AVERROR_INVALIDDATA;

        switch (sector[0x12] & CDXA_TYPE_MASK) {

        case CDXA_TYPE_DATA:
        case CDXA_TYPE_VIDEO:
            {

                int current_sector = AV_RL16(&sector[0x1C]);
                int sector_count   = AV_RL16(&sector[0x1E]);
                int frame_size = AV_RL32(&sector[0x24]);

                if(!(   frame_size>=0
                     && current_sector < sector_count
                     && sector_count*VIDEO_DATA_CHUNK_SIZE >=frame_size)){
                    av_log(s, AV_LOG_ERROR, "Invalid parameters %d %d %d\n", current_sector, sector_count, frame_size);
                    break;
                }

                if(str->channels[channel].video_stream_index < 0){
                    /* allocate a new AVStream */
                    st = avformat_new_stream(s, NULL);
                    if (!st)
                        return AVERROR(ENOMEM);
                    avpriv_set_pts_info(st, 64, 1, 15);

                    str->channels[channel].video_stream_index = st->index;

                    st->codecpar->codec_type = AVMEDIA_TYPE_VIDEO;
                    st->codecpar->codec_id   = AV_CODEC_ID_MDEC;
                    st->codecpar->codec_tag  = 0;  /* no fourcc */
                    st->codecpar->width      = AV_RL16(&sector[0x28]);
                    st->codecpar->height     = AV_RL16(&sector[0x2A]);
                }

                /* if this is the first sector of the frame, allocate a pkt */
                pkt = &str->channels[channel].tmp_pkt;

                if(pkt->size != sector_count*VIDEO_DATA_CHUNK_SIZE){
                    if(pkt->data)
                        av_log(s, AV_LOG_ERROR, "mismatching sector_count\n");
                    av_packet_unref(pkt);
                    if (av_new_packet(pkt, sector_count*VIDEO_DATA_CHUNK_SIZE))
                        return AVERROR(EIO);
                    memset(pkt->data, 0, sector_count*VIDEO_DATA_CHUNK_SIZE);

                    pkt->pos= avio_tell(pb) - RAW_CD_SECTOR_SIZE;
                    pkt->stream_index =
                        str->channels[channel].video_stream_index;
                }

                memcpy(pkt->data + current_sector*VIDEO_DATA_CHUNK_SIZE,
                       sector + VIDEO_DATA_HEADER_SIZE,
                       VIDEO_DATA_CHUNK_SIZE);

                if (current_sector == sector_count-1) {
                    pkt->size= frame_size;
                    *ret_pkt = *pkt;
                    pkt->data= NULL;
                    pkt->size= -1;
                    pkt->buf = NULL;
                    return 0;
                }

            }
            break;

        case CDXA_TYPE_AUDIO:
            if(str->channels[channel].audio_stream_index < 0){
                int fmt = sector[0x13];
                /* allocate a new AVStream */
                st = avformat_new_stream(s, NULL);
                if (!st)
                    return AVERROR(ENOMEM);

                str->channels[channel].audio_stream_index = st->index;

                st->codecpar->codec_type  = AVMEDIA_TYPE_AUDIO;
                st->codecpar->codec_id    = AV_CODEC_ID_ADPCM_XA;
                st->codecpar->codec_tag   = 0;  /* no fourcc */
                if (fmt & 1) {
                    st->codecpar->channels       = 2;
                    st->codecpar->channel_layout = AV_CH_LAYOUT_STEREO;
                } else {
                    st->codecpar->channels       = 1;
                    st->codecpar->channel_layout = AV_CH_LAYOUT_MONO;
                }
                st->codecpar->sample_rate = (fmt&4)?18900:37800;
            //    st->codecpar->bit_rate = 0; //FIXME;
                st->codecpar->block_align = 128;

                avpriv_set_pts_info(st, 64, 18 * 224 / st->codecpar->channels,
                                    st->codecpar->sample_rate);
                st->start_time = 0;
            }
            pkt = ret_pkt;
            if (av_new_packet(pkt, 2304))
                return AVERROR(EIO);
            memcpy(pkt->data,sector+24,2304);

            pkt->stream_index =
                str->channels[channel].audio_stream_index;
            pkt->duration = 1;
            return 0;
        default:
            av_log(s, AV_LOG_WARNING, "Unknown sector type %02X\n", sector[0x12]);
            /* drop the sector and move on */
            break;
        }

        if (avio_feof(pb))
            return AVERROR(EIO);
    }
}