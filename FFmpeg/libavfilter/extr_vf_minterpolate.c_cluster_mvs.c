#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int cid; int** mvs; } ;
struct TYPE_8__ {int nb; int* sum; } ;
struct TYPE_7__ {int b_height; int b_width; int log2_mb_size; TYPE_3__* int_blocks; TYPE_2__* clusters; } ;
typedef  TYPE_1__ MIContext ;
typedef  TYPE_2__ Cluster ;
typedef  TYPE_3__ Block ;

/* Variables and functions */
 scalar_t__ CLUSTER_THRESHOLD ; 
 scalar_t__ FFABS (int) ; 
 int FFMAX (int,int) ; 
 int FFMIN (int,int) ; 
 int NB_CLUSTERS ; 
 int var_size_bme (TYPE_1__*,TYPE_3__*,int,int,int) ; 

__attribute__((used)) static int cluster_mvs(MIContext *mi_ctx)
{
    int changed, c, c_max = 0;
    int mb_x, mb_y, x, y;
    int mv_x, mv_y, avg_x, avg_y, dx, dy;
    int d, ret;
    Block *block;
    Cluster *cluster, *cluster_new;

    do {
        changed = 0;
        for (mb_y = 0; mb_y < mi_ctx->b_height; mb_y++)
            for (mb_x = 0; mb_x < mi_ctx->b_width; mb_x++) {
                block = &mi_ctx->int_blocks[mb_x + mb_y * mi_ctx->b_width];
                c = block->cid;
                cluster = &mi_ctx->clusters[c];
                mv_x = block->mvs[0][0];
                mv_y = block->mvs[0][1];

                if (cluster->nb < 2)
                    continue;

                avg_x = cluster->sum[0] / cluster->nb;
                avg_y = cluster->sum[1] / cluster->nb;
                dx = avg_x - mv_x;
                dy = avg_y - mv_y;

                if (FFABS(dx) > CLUSTER_THRESHOLD || FFABS(dy) > CLUSTER_THRESHOLD) {

                    for (d = 1; d < 5; d++)
                        for (y = FFMAX(mb_y - d, 0); y < FFMIN(mb_y + d + 1, mi_ctx->b_height); y++)
                            for (x = FFMAX(mb_x - d, 0); x < FFMIN(mb_x + d + 1, mi_ctx->b_width); x++) {
                                Block *nb = &mi_ctx->int_blocks[x + y * mi_ctx->b_width];
                                if (nb->cid > block->cid) {
                                    if (nb->cid < c || c == block->cid)
                                        c = nb->cid;
                                }
                            }

                    if (c == block->cid)
                        c = c_max + 1;

                    if (c >= NB_CLUSTERS) {
                        continue;
                    }

                    cluster_new = &mi_ctx->clusters[c];
                    cluster_new->sum[0] += mv_x;
                    cluster_new->sum[1] += mv_y;
                    cluster->sum[0] -= mv_x;
                    cluster->sum[1] -= mv_y;
                    cluster_new->nb++;
                    cluster->nb--;

                    c_max = FFMAX(c_max, c);
                    block->cid = c;

                    changed = 1;
                }
            }
    } while (changed);

    /* find boundaries */
    for (mb_y = 0; mb_y < mi_ctx->b_height; mb_y++)
        for (mb_x = 0; mb_x < mi_ctx->b_width; mb_x++) {
            block = &mi_ctx->int_blocks[mb_x + mb_y * mi_ctx->b_width];
            for (y = FFMAX(mb_y - 1, 0); y < FFMIN(mb_y + 2, mi_ctx->b_height); y++)
                for (x = FFMAX(mb_x - 1, 0); x < FFMIN(mb_x + 2, mi_ctx->b_width); x++) {
                    dx = x - mb_x;
                    dy = y - mb_y;

                    if ((x - mb_x) && (y - mb_y) || !dx && !dy)
                        continue;

                    if (!mb_x || !mb_y || mb_x == mi_ctx->b_width - 1 || mb_y == mi_ctx->b_height - 1)
                        continue;

                    if (block->cid != mi_ctx->int_blocks[x + y * mi_ctx->b_width].cid) {
                        if (!dx && block->cid == mi_ctx->int_blocks[x + (mb_y - dy) * mi_ctx->b_width].cid ||
                            !dy && block->cid == mi_ctx->int_blocks[(mb_x - dx) + y * mi_ctx->b_width].cid) {
                            if (ret = var_size_bme(mi_ctx, block, mb_x << mi_ctx->log2_mb_size, mb_y << mi_ctx->log2_mb_size, mi_ctx->log2_mb_size))
                                return ret;
                        }
                    }
                }
        }

    return 0;
}