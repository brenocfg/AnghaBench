#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_13__ ;

/* Type definitions */
struct TYPE_24__ {TYPE_2__* priv; } ;
struct TYPE_23__ {TYPE_7__* dst; } ;
struct TYPE_22__ {int /*<<< orphan*/ * data; int /*<<< orphan*/ * linesize; } ;
struct TYPE_21__ {scalar_t__** mvs; int /*<<< orphan*/  sbad; } ;
struct TYPE_20__ {TYPE_5__* avf; int /*<<< orphan*/  blocks; } ;
struct TYPE_17__ {int /*<<< orphan*/  data_ref; int /*<<< orphan*/  data_cur; int /*<<< orphan*/  linesize; } ;
struct TYPE_19__ {scalar_t__ mi_mode; scalar_t__ me_method; int b_count; scalar_t__ me_mode; int b_height; int b_width; scalar_t__ mc_mode; int log2_mb_size; TYPE_1__* clusters; TYPE_4__* int_blocks; scalar_t__ vsbmc; TYPE_13__ me_ctx; TYPE_3__* frames; void** mv_table; } ;
struct TYPE_18__ {int nb; scalar_t__* sum; } ;
typedef  TYPE_2__ MIContext ;
typedef  TYPE_3__ Frame ;
typedef  TYPE_4__ Block ;
typedef  TYPE_5__ AVFrame ;
typedef  TYPE_6__ AVFilterLink ;
typedef  TYPE_7__ AVFilterContext ;

/* Variables and functions */
 scalar_t__ AV_ME_METHOD_EPZS ; 
 scalar_t__ MC_MODE_AOBMC ; 
 scalar_t__ ME_MODE_BIDIR ; 
 scalar_t__ ME_MODE_BILAT ; 
 scalar_t__ MI_MODE_MCI ; 
 int NB_CLUSTERS ; 
 int NB_FRAMES ; 
 int /*<<< orphan*/  av_frame_free (TYPE_5__**) ; 
 int /*<<< orphan*/  bilateral_me (TYPE_2__*) ; 
 int cluster_mvs (TYPE_2__*) ; 
 int /*<<< orphan*/  get_sbad (TYPE_13__*,int,int,scalar_t__,scalar_t__) ; 
 void* memcpy (void*,void*,int) ; 
 int /*<<< orphan*/  memmove (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  search_mv (TYPE_2__*,int /*<<< orphan*/ ,int,int,int) ; 

__attribute__((used)) static int inject_frame(AVFilterLink *inlink, AVFrame *avf_in)
{
    AVFilterContext *ctx = inlink->dst;
    MIContext *mi_ctx = ctx->priv;
    Frame frame_tmp;
    int mb_x, mb_y, dir;

    av_frame_free(&mi_ctx->frames[0].avf);
    frame_tmp = mi_ctx->frames[0];
    memmove(&mi_ctx->frames[0], &mi_ctx->frames[1], sizeof(mi_ctx->frames[0]) * (NB_FRAMES - 1));
    mi_ctx->frames[NB_FRAMES - 1] = frame_tmp;
    mi_ctx->frames[NB_FRAMES - 1].avf = avf_in;

    if (mi_ctx->mi_mode == MI_MODE_MCI) {

        if (mi_ctx->me_method == AV_ME_METHOD_EPZS) {
            mi_ctx->mv_table[2] = memcpy(mi_ctx->mv_table[2], mi_ctx->mv_table[1], sizeof(*mi_ctx->mv_table[1]) * mi_ctx->b_count);
            mi_ctx->mv_table[1] = memcpy(mi_ctx->mv_table[1], mi_ctx->mv_table[0], sizeof(*mi_ctx->mv_table[0]) * mi_ctx->b_count);
        }

        if (mi_ctx->me_mode == ME_MODE_BIDIR) {

            if (mi_ctx->frames[1].avf) {
                for (dir = 0; dir < 2; dir++) {
                    mi_ctx->me_ctx.linesize = mi_ctx->frames[2].avf->linesize[0];
                    mi_ctx->me_ctx.data_cur = mi_ctx->frames[2].avf->data[0];
                    mi_ctx->me_ctx.data_ref = mi_ctx->frames[dir ? 3 : 1].avf->data[0];

                    for (mb_y = 0; mb_y < mi_ctx->b_height; mb_y++)
                        for (mb_x = 0; mb_x < mi_ctx->b_width; mb_x++)
                            search_mv(mi_ctx, mi_ctx->frames[2].blocks, mb_x, mb_y, dir);
                }
            }

        } else if (mi_ctx->me_mode == ME_MODE_BILAT) {
            Block *block;
            int i, ret;

            if (!mi_ctx->frames[0].avf)
                return 0;

            mi_ctx->me_ctx.linesize = mi_ctx->frames[0].avf->linesize[0];
            mi_ctx->me_ctx.data_cur = mi_ctx->frames[1].avf->data[0];
            mi_ctx->me_ctx.data_ref = mi_ctx->frames[2].avf->data[0];

            bilateral_me(mi_ctx);

            if (mi_ctx->mc_mode == MC_MODE_AOBMC) {

                for (mb_y = 0; mb_y < mi_ctx->b_height; mb_y++)
                    for (mb_x = 0; mb_x < mi_ctx->b_width; mb_x++) {
                        int x_mb = mb_x << mi_ctx->log2_mb_size;
                        int y_mb = mb_y << mi_ctx->log2_mb_size;
                        block = &mi_ctx->int_blocks[mb_x + mb_y * mi_ctx->b_width];

                        block->sbad = get_sbad(&mi_ctx->me_ctx, x_mb, y_mb, x_mb + block->mvs[0][0], y_mb + block->mvs[0][1]);
                    }
            }

            if (mi_ctx->vsbmc) {

                for (i = 0; i < NB_CLUSTERS; i++) {
                    mi_ctx->clusters[i].sum[0] = 0;
                    mi_ctx->clusters[i].sum[1] = 0;
                    mi_ctx->clusters[i].nb = 0;
                }

                for (mb_y = 0; mb_y < mi_ctx->b_height; mb_y++)
                    for (mb_x = 0; mb_x < mi_ctx->b_width; mb_x++) {
                        block = &mi_ctx->int_blocks[mb_x + mb_y * mi_ctx->b_width];

                        mi_ctx->clusters[0].sum[0] += block->mvs[0][0];
                        mi_ctx->clusters[0].sum[1] += block->mvs[0][1];
                    }

                mi_ctx->clusters[0].nb = mi_ctx->b_count;

                if (ret = cluster_mvs(mi_ctx))
                    return ret;
            }
        }
    }

    return 0;
}