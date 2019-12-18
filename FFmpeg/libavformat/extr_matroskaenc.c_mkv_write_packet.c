#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_23__ {TYPE_3__** streams; int /*<<< orphan*/  pb; TYPE_4__* priv_data; } ;
struct TYPE_22__ {size_t stream_index; int flags; scalar_t__ dts; scalar_t__ pts; scalar_t__ size; } ;
struct TYPE_21__ {scalar_t__ cluster_pts; int cluster_pos; scalar_t__ cluster_time_limit; int cluster_size_limit; TYPE_5__ cur_audio_pkt; scalar_t__ is_dash; scalar_t__ have_video; int /*<<< orphan*/  cluster_bc; TYPE_2__* tracks; } ;
struct TYPE_20__ {int /*<<< orphan*/  time_base; TYPE_1__* codecpar; } ;
struct TYPE_19__ {scalar_t__ ts_offset; scalar_t__ write_dts; } ;
struct TYPE_18__ {int codec_type; } ;
typedef  TYPE_4__ MatroskaMuxContext ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int /*<<< orphan*/  AVIO_DATA_MARKER_BOUNDARY_POINT ; 
 int /*<<< orphan*/  AVIO_DATA_MARKER_SYNC_POINT ; 
 int AVMEDIA_TYPE_AUDIO ; 
 int AVMEDIA_TYPE_VIDEO ; 
 int /*<<< orphan*/  AV_LOG_ERROR ; 
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  AV_TIME_BASE_Q ; 
 int /*<<< orphan*/  av_log (TYPE_6__*,int /*<<< orphan*/ ,char*,int) ; 
 int av_packet_ref (TYPE_5__*,TYPE_5__*) ; 
 int /*<<< orphan*/  av_packet_unref (TYPE_5__*) ; 
 int /*<<< orphan*/  av_rescale_q (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_write_marker (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mkv_check_new_extra_data (TYPE_6__*,TYPE_5__*) ; 
 int /*<<< orphan*/  mkv_end_cluster (TYPE_6__*) ; 
 int mkv_write_packet_internal (TYPE_6__*,TYPE_5__*,int) ; 

__attribute__((used)) static int mkv_write_packet(AVFormatContext *s, AVPacket *pkt)
{
    MatroskaMuxContext *mkv = s->priv_data;
    int codec_type          = s->streams[pkt->stream_index]->codecpar->codec_type;
    int keyframe            = !!(pkt->flags & AV_PKT_FLAG_KEY);
    int cluster_size;
    int64_t cluster_time;
    int ret;
    int start_new_cluster;

    ret = mkv_check_new_extra_data(s, pkt);
    if (ret < 0)
        return ret;

    if (mkv->tracks[pkt->stream_index].write_dts)
        cluster_time = pkt->dts - mkv->cluster_pts;
    else
        cluster_time = pkt->pts - mkv->cluster_pts;
    cluster_time += mkv->tracks[pkt->stream_index].ts_offset;

    // start a new cluster every 5 MB or 5 sec, or 32k / 1 sec for streaming or
    // after 4k and on a keyframe
    cluster_size = avio_tell(mkv->cluster_bc);

    if (mkv->is_dash && codec_type == AVMEDIA_TYPE_VIDEO) {
        // WebM DASH specification states that the first block of every cluster
        // has to be a key frame. So for DASH video, we only create a cluster
        // on seeing key frames.
        start_new_cluster = keyframe;
    } else if (mkv->is_dash && codec_type == AVMEDIA_TYPE_AUDIO &&
               (mkv->cluster_pos == -1 ||
                cluster_time > mkv->cluster_time_limit)) {
        // For DASH audio, we create a Cluster based on cluster_time_limit
        start_new_cluster = 1;
    } else if (!mkv->is_dash &&
               (cluster_size > mkv->cluster_size_limit ||
                cluster_time > mkv->cluster_time_limit ||
                (codec_type == AVMEDIA_TYPE_VIDEO && keyframe &&
                 cluster_size > 4 * 1024))) {
        start_new_cluster = 1;
    } else {
        start_new_cluster = 0;
    }

    if (mkv->cluster_pos != -1 && start_new_cluster) {
        mkv_end_cluster(s);
    }

    if (!mkv->cluster_pos)
        avio_write_marker(s->pb,
                          av_rescale_q(pkt->dts, s->streams[pkt->stream_index]->time_base, AV_TIME_BASE_Q),
                          keyframe && (mkv->have_video ? codec_type == AVMEDIA_TYPE_VIDEO : 1) ? AVIO_DATA_MARKER_SYNC_POINT : AVIO_DATA_MARKER_BOUNDARY_POINT);

    // check if we have an audio packet cached
    if (mkv->cur_audio_pkt.size > 0) {
        // for DASH audio, a CuePoint has to be added when there is a new cluster.
        ret = mkv_write_packet_internal(s, &mkv->cur_audio_pkt,
                                        mkv->is_dash ? start_new_cluster : 0);
        av_packet_unref(&mkv->cur_audio_pkt);
        if (ret < 0) {
            av_log(s, AV_LOG_ERROR,
                   "Could not write cached audio packet ret:%d\n", ret);
            return ret;
        }
    }

    // buffer an audio packet to ensure the packet containing the video
    // keyframe's timecode is contained in the same cluster for WebM
    if (codec_type == AVMEDIA_TYPE_AUDIO) {
        if (pkt->size > 0)
            ret = av_packet_ref(&mkv->cur_audio_pkt, pkt);
    } else
        ret = mkv_write_packet_internal(s, pkt, 0);
    return ret;
}