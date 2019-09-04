#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_19__ {scalar_t__ nb_elem; TYPE_5__* elem; } ;
struct TYPE_20__ {int /*<<< orphan*/  timecode; TYPE_6__ blocks; } ;
struct TYPE_16__ {int /*<<< orphan*/  size; int /*<<< orphan*/ * data; } ;
struct TYPE_15__ {scalar_t__ size; int /*<<< orphan*/  pos; scalar_t__ data; int /*<<< orphan*/  buf; } ;
struct TYPE_18__ {scalar_t__ reference; int /*<<< orphan*/  discard_padding; TYPE_3__ additional; int /*<<< orphan*/  additional_id; scalar_t__ duration; TYPE_2__ bin; scalar_t__ non_simple; } ;
struct TYPE_17__ {int current_cluster_pos; scalar_t__ current_cluster_num_blocks; TYPE_7__ current_cluster; scalar_t__ current_id; TYPE_1__* ctx; } ;
struct TYPE_14__ {int /*<<< orphan*/  pb; } ;
typedef  TYPE_4__ MatroskaDemuxContext ;
typedef  int /*<<< orphan*/  MatroskaCluster ;
typedef  TYPE_5__ MatroskaBlock ;
typedef  TYPE_6__ EbmlList ;

/* Variables and functions */
 scalar_t__ INT64_MIN ; 
 int avio_tell (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ebml_free (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  ebml_level_end (TYPE_4__*) ; 
 int ebml_parse (TYPE_4__*,int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  matroska_cluster ; 
 int /*<<< orphan*/  matroska_cluster_incremental_parsing ; 
 int /*<<< orphan*/  matroska_clusters_incremental ; 
 int matroska_parse_block (TYPE_4__*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int matroska_parse_cluster_incremental(MatroskaDemuxContext *matroska)
{
    EbmlList *blocks_list;
    MatroskaBlock *blocks;
    int i, res;
    res = ebml_parse(matroska,
                     matroska_cluster_incremental_parsing,
                     &matroska->current_cluster);
    if (res == 1) {
        /* New Cluster */
        if (matroska->current_cluster_pos)
            ebml_level_end(matroska);
        ebml_free(matroska_cluster, &matroska->current_cluster);
        memset(&matroska->current_cluster, 0, sizeof(MatroskaCluster));
        matroska->current_cluster_num_blocks = 0;
        matroska->current_cluster_pos        = avio_tell(matroska->ctx->pb);
        /* sizeof the ID which was already read */
        if (matroska->current_id)
            matroska->current_cluster_pos -= 4;
        res = ebml_parse(matroska,
                         matroska_clusters_incremental,
                         &matroska->current_cluster);
        /* Try parsing the block again. */
        if (res == 1)
            res = ebml_parse(matroska,
                             matroska_cluster_incremental_parsing,
                             &matroska->current_cluster);
    }

    if (!res &&
        matroska->current_cluster_num_blocks <
        matroska->current_cluster.blocks.nb_elem) {
        blocks_list = &matroska->current_cluster.blocks;
        blocks      = blocks_list->elem;

        matroska->current_cluster_num_blocks = blocks_list->nb_elem;
        i                                    = blocks_list->nb_elem - 1;
        if (blocks[i].bin.size > 0 && blocks[i].bin.data) {
            int is_keyframe = blocks[i].non_simple ? blocks[i].reference == INT64_MIN : -1;
            uint8_t* additional = blocks[i].additional.size > 0 ?
                                    blocks[i].additional.data : NULL;
            if (!blocks[i].non_simple)
                blocks[i].duration = 0;
            res = matroska_parse_block(matroska, blocks[i].bin.buf, blocks[i].bin.data,
                                       blocks[i].bin.size, blocks[i].bin.pos,
                                       matroska->current_cluster.timecode,
                                       blocks[i].duration, is_keyframe,
                                       additional, blocks[i].additional_id,
                                       blocks[i].additional.size,
                                       matroska->current_cluster_pos,
                                       blocks[i].discard_padding);
        }
    }

    return res;
}