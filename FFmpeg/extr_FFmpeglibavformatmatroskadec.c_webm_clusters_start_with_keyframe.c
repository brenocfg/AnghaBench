#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_12__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_19__ {int /*<<< orphan*/  pb; TYPE_12__** streams; TYPE_4__* priv_data; } ;
struct TYPE_18__ {int flags; } ;
struct TYPE_17__ {TYPE_3__* queue; scalar_t__ current_id; TYPE_2__* ctx; } ;
struct TYPE_16__ {TYPE_5__ pkt; } ;
struct TYPE_15__ {int /*<<< orphan*/  pb; } ;
struct TYPE_14__ {int pos; } ;
struct TYPE_13__ {scalar_t__ nb_index_entries; TYPE_1__* index_entries; } ;
typedef  TYPE_4__ MatroskaDemuxContext ;
typedef  TYPE_5__ AVPacket ;
typedef  TYPE_6__ AVFormatContext ;

/* Variables and functions */
 int AV_PKT_FLAG_KEY ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int av_index_search_timestamp (TYPE_12__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avio_seek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ebml_read_length (TYPE_4__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ebml_read_num (TYPE_4__*,int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  matroska_clear_queue (TYPE_4__*) ; 
 scalar_t__ matroska_parse_cluster (TYPE_4__*) ; 

__attribute__((used)) static int webm_clusters_start_with_keyframe(AVFormatContext *s)
{
    MatroskaDemuxContext *matroska = s->priv_data;
    int64_t cluster_pos, before_pos;
    int index, rv = 1;
    if (s->streams[0]->nb_index_entries <= 0) return 0;
    // seek to the first cluster using cues.
    index = av_index_search_timestamp(s->streams[0], 0, 0);
    if (index < 0)  return 0;
    cluster_pos = s->streams[0]->index_entries[index].pos;
    before_pos = avio_tell(s->pb);
    while (1) {
        int64_t cluster_id = 0, cluster_length = 0;
        AVPacket *pkt;
        avio_seek(s->pb, cluster_pos, SEEK_SET);
        // read cluster id and length
        ebml_read_num(matroska, matroska->ctx->pb, 4, &cluster_id);
        ebml_read_length(matroska, matroska->ctx->pb, &cluster_length);
        if (cluster_id != 0xF43B675) { // done with all clusters
            break;
        }
        avio_seek(s->pb, cluster_pos, SEEK_SET);
        matroska->current_id = 0;
        matroska_clear_queue(matroska);
        if (matroska_parse_cluster(matroska) < 0 ||
            !matroska->queue) {
            break;
        }
        pkt = &matroska->queue->pkt;
        cluster_pos += cluster_length + 12; // 12 is the offset of the cluster id and length.
        if (!(pkt->flags & AV_PKT_FLAG_KEY)) {
            rv = 0;
            break;
        }
    }
    avio_seek(s->pb, before_pos, SEEK_SET);
    return rv;
}