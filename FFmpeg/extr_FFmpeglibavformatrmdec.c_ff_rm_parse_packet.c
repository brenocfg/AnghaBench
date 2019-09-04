#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
typedef  void* int64_t ;
struct TYPE_27__ {TYPE_4__* priv_data; } ;
struct TYPE_26__ {int /*<<< orphan*/  flags; void* pts; int /*<<< orphan*/  stream_index; } ;
struct TYPE_25__ {TYPE_2__* codecpar; int /*<<< orphan*/  index; int /*<<< orphan*/  id; } ;
struct TYPE_24__ {int audio_pkt_cnt; int /*<<< orphan*/  audio_stream_num; int /*<<< orphan*/  current_stream; } ;
struct TYPE_21__ {int /*<<< orphan*/  data; } ;
struct TYPE_23__ {int deint_id; int sub_packet_size; int coded_framesize; int sub_packet_h; int sub_packet_cnt; int audio_framesize; int* sub_packet_lengths; void* audiotimestamp; TYPE_1__ pkt; } ;
struct TYPE_22__ {scalar_t__ codec_type; int block_align; } ;
typedef  TYPE_3__ RMStream ;
typedef  TYPE_4__ RMDemuxContext ;
typedef  TYPE_5__ AVStream ;
typedef  TYPE_6__ AVPacket ;
typedef  int /*<<< orphan*/  AVIOContext ;
typedef  TYPE_7__ AVFormatContext ;

/* Variables and functions */
 int AVERROR_INVALIDDATA ; 
 scalar_t__ AVMEDIA_TYPE_AUDIO ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_PKT_FLAG_KEY ; 
#define  DEINT_ID_GENR 130 
#define  DEINT_ID_INT4 129 
#define  DEINT_ID_SIPR 128 
 int DEINT_ID_VBRF ; 
 int DEINT_ID_VBRS ; 
 int av_get_packet (int /*<<< orphan*/ *,TYPE_6__*,int) ; 
 int /*<<< orphan*/  av_log (TYPE_7__*,int /*<<< orphan*/ ,char*,int) ; 
 int avio_rb16 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ff_rm_reorder_sipr_data (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  readfull (TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rm_ac3_swap_bytes (TYPE_5__*,TYPE_6__*) ; 
 int rm_assemble_video_frame (TYPE_7__*,int /*<<< orphan*/ *,TYPE_4__*,TYPE_3__*,TYPE_6__*,int,int*,void**) ; 

int
ff_rm_parse_packet (AVFormatContext *s, AVIOContext *pb,
                    AVStream *st, RMStream *ast, int len, AVPacket *pkt,
                    int *seq, int flags, int64_t timestamp)
{
    RMDemuxContext *rm = s->priv_data;
    int ret;

    if (st->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
        rm->current_stream= st->id;
        ret = rm_assemble_video_frame(s, pb, rm, ast, pkt, len, seq, &timestamp);
        if(ret)
            return ret < 0 ? ret : -1; //got partial frame or error
    } else if (st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
        if ((ast->deint_id == DEINT_ID_GENR) ||
            (ast->deint_id == DEINT_ID_INT4) ||
            (ast->deint_id == DEINT_ID_SIPR)) {
            int x;
            int sps = ast->sub_packet_size;
            int cfs = ast->coded_framesize;
            int h = ast->sub_packet_h;
            int y = ast->sub_packet_cnt;
            int w = ast->audio_framesize;

            if (flags & 2)
                y = ast->sub_packet_cnt = 0;
            if (!y)
                ast->audiotimestamp = timestamp;

            switch (ast->deint_id) {
                case DEINT_ID_INT4:
                    for (x = 0; x < h/2; x++)
                        readfull(s, pb, ast->pkt.data+x*2*w+y*cfs, cfs);
                    break;
                case DEINT_ID_GENR:
                    for (x = 0; x < w/sps; x++)
                        readfull(s, pb, ast->pkt.data+sps*(h*x+((h+1)/2)*(y&1)+(y>>1)), sps);
                    break;
                case DEINT_ID_SIPR:
                    readfull(s, pb, ast->pkt.data + y * w, w);
                    break;
            }

            if (++(ast->sub_packet_cnt) < h)
                return -1;
            if (ast->deint_id == DEINT_ID_SIPR)
                ff_rm_reorder_sipr_data(ast->pkt.data, h, w);

             ast->sub_packet_cnt = 0;
             rm->audio_stream_num = st->index;
            if (st->codecpar->block_align <= 0) {
                av_log(s, AV_LOG_ERROR, "Invalid block alignment %d\n", st->codecpar->block_align);
                return AVERROR_INVALIDDATA;
            }
             rm->audio_pkt_cnt = h * w / st->codecpar->block_align;
        } else if ((ast->deint_id == DEINT_ID_VBRF) ||
                   (ast->deint_id == DEINT_ID_VBRS)) {
            int x;
            rm->audio_stream_num = st->index;
            ast->sub_packet_cnt = (avio_rb16(pb) & 0xf0) >> 4;
            if (ast->sub_packet_cnt) {
                for (x = 0; x < ast->sub_packet_cnt; x++)
                    ast->sub_packet_lengths[x] = avio_rb16(pb);
                rm->audio_pkt_cnt = ast->sub_packet_cnt;
                ast->audiotimestamp = timestamp;
            } else
                return -1;
        } else {
            ret = av_get_packet(pb, pkt, len);
            if (ret < 0)
                return ret;
            rm_ac3_swap_bytes(st, pkt);
        }
    } else {
        ret = av_get_packet(pb, pkt, len);
        if (ret < 0)
            return ret;
    }

    pkt->stream_index = st->index;

    pkt->pts = timestamp;
    if (flags & 2)
        pkt->flags |= AV_PKT_FLAG_KEY;

    return st->codecpar->codec_type == AVMEDIA_TYPE_AUDIO ? rm->audio_pkt_cnt : 0;
}