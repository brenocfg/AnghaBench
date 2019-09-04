#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_32__   TYPE_7__ ;
typedef  struct TYPE_31__   TYPE_6__ ;
typedef  struct TYPE_30__   TYPE_5__ ;
typedef  struct TYPE_29__   TYPE_4__ ;
typedef  struct TYPE_28__   TYPE_3__ ;
typedef  struct TYPE_27__   TYPE_2__ ;
typedef  struct TYPE_26__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
typedef  scalar_t__ int16_t ;
typedef  int /*<<< orphan*/  ebml_master ;
struct TYPE_32__ {scalar_t__ codec_type; scalar_t__ codec_id; } ;
struct TYPE_31__ {TYPE_5__* pb; TYPE_1__** streams; TYPE_3__* priv_data; } ;
struct TYPE_30__ {int seekable; } ;
struct TYPE_29__ {size_t stream_index; int flags; int duration; scalar_t__ dts; scalar_t__ pts; int /*<<< orphan*/  size; } ;
struct TYPE_28__ {int dash_track_number; int cluster_pos; scalar_t__ cluster_pts; int duration; int* stream_durations; int /*<<< orphan*/  cues; TYPE_5__* dyn_bc; int /*<<< orphan*/  cluster; TYPE_2__* tracks; scalar_t__ is_dash; } ;
struct TYPE_27__ {scalar_t__ ts_offset; scalar_t__ write_dts; } ;
struct TYPE_26__ {TYPE_7__* codecpar; } ;
typedef  TYPE_3__ MatroskaMuxContext ;
typedef  TYPE_4__ AVPacket ;
typedef  TYPE_5__ AVIOContext ;
typedef  TYPE_6__ AVFormatContext ;
typedef  TYPE_7__ AVCodecParameters ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int AVIO_SEEKABLE_NORMAL ; 
 scalar_t__ AVMEDIA_TYPE_SUBTITLE ; 
 scalar_t__ AVMEDIA_TYPE_VIDEO ; 
 scalar_t__ AV_CODEC_ID_WEBVTT ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int /*<<< orphan*/  AV_LOG_WARNING ; 
 scalar_t__ AV_NOPTS_VALUE ; 
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  EINVAL ; 
 int FFMAX (int,scalar_t__) ; 
 int /*<<< orphan*/  MATROSKA_ID_BLOCK ; 
 int /*<<< orphan*/  MATROSKA_ID_BLOCKDURATION ; 
 int /*<<< orphan*/  MATROSKA_ID_BLOCKGROUP ; 
 int /*<<< orphan*/  MATROSKA_ID_CLUSTER ; 
 int /*<<< orphan*/  MATROSKA_ID_CLUSTERTIMECODE ; 
 int /*<<< orphan*/  MATROSKA_ID_SIMPLEBLOCK ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*) ; 
 void* avio_tell (TYPE_5__*) ; 
 int /*<<< orphan*/  end_ebml_master (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int mkv_add_cuepoint (int /*<<< orphan*/ ,size_t,int,scalar_t__,int,scalar_t__,int) ; 
 int /*<<< orphan*/  mkv_blockgroup_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mkv_start_new_cluster (TYPE_6__*,TYPE_4__*) ; 
 int /*<<< orphan*/  mkv_write_block (TYPE_6__*,TYPE_5__*,int /*<<< orphan*/ ,TYPE_4__*,int) ; 
 int mkv_write_vtt_blocks (TYPE_6__*,TYPE_5__*,TYPE_4__*) ; 
 int /*<<< orphan*/  put_ebml_uint (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  start_ebml_master (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int start_ebml_master_crc32 (TYPE_5__*,TYPE_5__**,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mkv_write_packet_internal(AVFormatContext *s, AVPacket *pkt, int add_cue)
{
    MatroskaMuxContext *mkv = s->priv_data;
    AVIOContext *pb         = s->pb;
    AVCodecParameters *par  = s->streams[pkt->stream_index]->codecpar;
    int keyframe            = !!(pkt->flags & AV_PKT_FLAG_KEY);
    int duration            = pkt->duration;
    int ret;
    int64_t ts = mkv->tracks[pkt->stream_index].write_dts ? pkt->dts : pkt->pts;
    int64_t relative_packet_pos;
    int dash_tracknum = mkv->is_dash ? mkv->dash_track_number : pkt->stream_index + 1;

    if (ts == AV_NOPTS_VALUE) {
        av_log(s, AV_LOG_ERROR, "Can't write packet with unknown timestamp\n");
        return AVERROR(EINVAL);
    }
    ts += mkv->tracks[pkt->stream_index].ts_offset;

    if (mkv->cluster_pos != -1) {
        int64_t cluster_time = ts - mkv->cluster_pts + mkv->tracks[pkt->stream_index].ts_offset;
        if ((int16_t)cluster_time != cluster_time) {
            av_log(s, AV_LOG_WARNING, "Starting new cluster due to timestamp\n");
            mkv_start_new_cluster(s, pkt);
        }
    }

    if (mkv->cluster_pos == -1) {
        mkv->cluster_pos = avio_tell(s->pb);
        ret = start_ebml_master_crc32(s->pb, &mkv->dyn_bc, mkv, &mkv->cluster, MATROSKA_ID_CLUSTER, 0);
        if (ret < 0)
            return ret;
        put_ebml_uint(mkv->dyn_bc, MATROSKA_ID_CLUSTERTIMECODE, FFMAX(0, ts));
        mkv->cluster_pts = FFMAX(0, ts);
    }
    pb = mkv->dyn_bc;

    relative_packet_pos = avio_tell(pb);

    if (par->codec_type != AVMEDIA_TYPE_SUBTITLE) {
        mkv_write_block(s, pb, MATROSKA_ID_SIMPLEBLOCK, pkt, keyframe);
        if ((s->pb->seekable & AVIO_SEEKABLE_NORMAL) && (par->codec_type == AVMEDIA_TYPE_VIDEO && keyframe || add_cue)) {
            ret = mkv_add_cuepoint(mkv->cues, pkt->stream_index, dash_tracknum, ts, mkv->cluster_pos, relative_packet_pos, -1);
            if (ret < 0) return ret;
        }
    } else {
        if (par->codec_id == AV_CODEC_ID_WEBVTT) {
            duration = mkv_write_vtt_blocks(s, pb, pkt);
        } else {
            ebml_master blockgroup = start_ebml_master(pb, MATROSKA_ID_BLOCKGROUP,
                                                       mkv_blockgroup_size(pkt->size));

#if FF_API_CONVERGENCE_DURATION
FF_DISABLE_DEPRECATION_WARNINGS
            /* For backward compatibility, prefer convergence_duration. */
            if (pkt->convergence_duration > 0) {
                duration = pkt->convergence_duration;
            }
FF_ENABLE_DEPRECATION_WARNINGS
#endif
            /* All subtitle blocks are considered to be keyframes. */
            mkv_write_block(s, pb, MATROSKA_ID_BLOCK, pkt, 1);
            put_ebml_uint(pb, MATROSKA_ID_BLOCKDURATION, duration);
            end_ebml_master(pb, blockgroup);
        }

        if (s->pb->seekable & AVIO_SEEKABLE_NORMAL) {
            ret = mkv_add_cuepoint(mkv->cues, pkt->stream_index, dash_tracknum, ts,
                                   mkv->cluster_pos, relative_packet_pos, duration);
            if (ret < 0)
                return ret;
        }
    }

    mkv->duration = FFMAX(mkv->duration, ts + duration);

    if (mkv->stream_durations)
        mkv->stream_durations[pkt->stream_index] =
            FFMAX(mkv->stream_durations[pkt->stream_index], ts + duration);

    return 0;
}