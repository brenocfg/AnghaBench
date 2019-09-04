#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/ * pb; TYPE_2__* priv_data; } ;
struct TYPE_19__ {int duration; int /*<<< orphan*/  flags; int /*<<< orphan*/  stream_index; } ;
struct TYPE_18__ {int /*<<< orphan*/  start_time; TYPE_1__* codecpar; int /*<<< orphan*/  index; } ;
struct TYPE_17__ {int is_finished; int sample_rate; int /*<<< orphan*/  nframes; int /*<<< orphan*/  audio_index; int /*<<< orphan*/  palette; } ;
struct TYPE_16__ {int channels; int bits_per_coded_sample; int sample_rate; int bit_rate; int /*<<< orphan*/  channel_layout; int /*<<< orphan*/  codec_id; int /*<<< orphan*/  codec_type; } ;
typedef  TYPE_2__ BVID_DemuxContext ;
typedef  TYPE_3__ AVStream ;
typedef  TYPE_4__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_5__ AVFormatContext ;

/* Variables and functions */
#define  AUDIO_BLOCK 134 
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVERROR_EOF ; 
 int AVERROR_INVALIDDATA ; 
 int /*<<< orphan*/  AVMEDIA_TYPE_AUDIO ; 
 int /*<<< orphan*/  AV_CH_LAYOUT_MONO ; 
 int /*<<< orphan*/  AV_CODEC_ID_PCM_U8 ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_VERBOSE ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  BVID_PALETTE_SIZE ; 
 int /*<<< orphan*/  EIO ; 
 int /*<<< orphan*/  ENOMEM ; 
#define  EOF_BLOCK 133 
#define  FIRST_AUDIO_BLOCK 132 
#define  PALETTE_BLOCK 131 
#define  VIDEO_I_FRAME 130 
#define  VIDEO_P_FRAME 129 
#define  VIDEO_YOFF_P_FRAME 128 
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  av_malloc (int /*<<< orphan*/ ) ; 
 TYPE_3__* avformat_new_stream (TYPE_5__*,int /*<<< orphan*/ *) ; 
 scalar_t__ avio_feof (int /*<<< orphan*/ *) ; 
 int avio_r8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avio_read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avio_rl16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avpriv_set_pts_info (TYPE_3__*,int,int,int) ; 
 int read_frame (TYPE_2__*,int /*<<< orphan*/ *,TYPE_4__*,unsigned char,TYPE_5__*) ; 

__attribute__((used)) static int vid_read_packet(AVFormatContext *s,
                           AVPacket *pkt)
{
    BVID_DemuxContext *vid = s->priv_data;
    AVIOContext *pb = s->pb;
    unsigned char block_type;
    int audio_length;
    int ret_value;

    if(vid->is_finished || avio_feof(pb))
        return AVERROR_EOF;

    block_type = avio_r8(pb);
    switch(block_type){
        case PALETTE_BLOCK:
            if (vid->palette) {
                av_log(s, AV_LOG_WARNING, "discarding unused palette\n");
                av_freep(&vid->palette);
            }
            vid->palette = av_malloc(BVID_PALETTE_SIZE);
            if (!vid->palette)
                return AVERROR(ENOMEM);
            if (avio_read(pb, vid->palette, BVID_PALETTE_SIZE) != BVID_PALETTE_SIZE) {
                av_freep(&vid->palette);
                return AVERROR(EIO);
            }
            return vid_read_packet(s, pkt);

        case FIRST_AUDIO_BLOCK:
            avio_rl16(pb);
            // soundblaster DAC used for sample rate, as on specification page (link above)
            vid->sample_rate = 1000000 / (256 - avio_r8(pb));
        case AUDIO_BLOCK:
            if (vid->audio_index < 0) {
                AVStream *st = avformat_new_stream(s, NULL);
                if (!st)
                    return AVERROR(ENOMEM);
                vid->audio_index                 = st->index;
                st->codecpar->codec_type            = AVMEDIA_TYPE_AUDIO;
                st->codecpar->codec_id              = AV_CODEC_ID_PCM_U8;
                st->codecpar->channels              = 1;
                st->codecpar->channel_layout        = AV_CH_LAYOUT_MONO;
                st->codecpar->bits_per_coded_sample = 8;
                st->codecpar->sample_rate           = vid->sample_rate;
                st->codecpar->bit_rate              = 8 * st->codecpar->sample_rate;
                st->start_time                   = 0;
                avpriv_set_pts_info(st, 64, 1, vid->sample_rate);
            }
            audio_length = avio_rl16(pb);
            if ((ret_value = av_get_packet(pb, pkt, audio_length)) != audio_length) {
                if (ret_value < 0)
                    return ret_value;
                av_log(s, AV_LOG_ERROR, "incomplete audio block\n");
                return AVERROR(EIO);
            }
            pkt->stream_index = vid->audio_index;
            pkt->duration     = audio_length;
            pkt->flags |= AV_PKT_FLAG_KEY;
            return 0;

        case VIDEO_P_FRAME:
        case VIDEO_YOFF_P_FRAME:
        case VIDEO_I_FRAME:
            return read_frame(vid, pb, pkt, block_type, s);

        case EOF_BLOCK:
            if(vid->nframes != 0)
                av_log(s, AV_LOG_VERBOSE, "reached terminating character but not all frames read.\n");
            vid->is_finished = 1;
            return AVERROR(EIO);
        default:
            av_log(s, AV_LOG_ERROR, "unknown block (character = %c, decimal = %d, hex = %x)!!!\n",
                   block_type, block_type, block_type);
            return AVERROR_INVALIDDATA;
    }
}