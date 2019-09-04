#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int int64_t ;
struct TYPE_18__ {int nb_elem; TYPE_5__* elem; } ;
struct TYPE_14__ {scalar_t__ size; int /*<<< orphan*/  pos; scalar_t__ data; int /*<<< orphan*/  buf; } ;
struct TYPE_17__ {scalar_t__ reference; int /*<<< orphan*/  discard_padding; int /*<<< orphan*/  duration; TYPE_2__ bin; scalar_t__ non_simple; } ;
struct TYPE_16__ {int /*<<< orphan*/  timecode; TYPE_6__ blocks; int /*<<< orphan*/  member_0; } ;
struct TYPE_15__ {scalar_t__ current_id; TYPE_1__* ctx; int /*<<< orphan*/  contains_ssa; } ;
struct TYPE_13__ {int /*<<< orphan*/  pb; } ;
typedef  TYPE_3__ MatroskaDemuxContext ;
typedef  TYPE_4__ MatroskaCluster ;
typedef  TYPE_5__ MatroskaBlock ;
typedef  TYPE_6__ EbmlList ;

/* Variables and functions */
 scalar_t__ INT64_MIN ; 
 int avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ebml_free (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int ebml_parse (TYPE_3__*,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  matroska_cluster ; 
 int /*<<< orphan*/  matroska_clusters ; 
 int matroska_parse_block (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int matroska_parse_cluster_incremental (TYPE_3__*) ; 

__attribute__((used)) static int matroska_parse_cluster(MatroskaDemuxContext *matroska)
{
    MatroskaCluster cluster = { 0 };
    EbmlList *blocks_list;
    MatroskaBlock *blocks;
    int i, res;
    int64_t pos;

    if (!matroska->contains_ssa)
        return matroska_parse_cluster_incremental(matroska);
    pos = avio_tell(matroska->ctx->pb);
    if (matroska->current_id)
        pos -= 4;  /* sizeof the ID which was already read */
    res         = ebml_parse(matroska, matroska_clusters, &cluster);
    blocks_list = &cluster.blocks;
    blocks      = blocks_list->elem;
    for (i = 0; i < blocks_list->nb_elem; i++)
        if (blocks[i].bin.size > 0 && blocks[i].bin.data) {
            int is_keyframe = blocks[i].non_simple ? blocks[i].reference == INT64_MIN : -1;
            res = matroska_parse_block(matroska, blocks[i].bin.buf, blocks[i].bin.data,
                                       blocks[i].bin.size, blocks[i].bin.pos,
                                       cluster.timecode, blocks[i].duration,
                                       is_keyframe, NULL, 0, 0, pos,
                                       blocks[i].discard_padding);
        }
    ebml_free(matroska_cluster, &cluster);
    return res;
}