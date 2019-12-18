#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
struct TYPE_10__ {int** mvs; int sbad; } ;
struct TYPE_9__ {scalar_t__ mc_mode; int b_height; int b_width; int log2_mb_size; int mb_size; TYPE_4__* int_blocks; int /*<<< orphan*/ * pixel_refs; int /*<<< orphan*/ * pixel_weights; int /*<<< orphan*/ * pixel_mvs; int /*<<< orphan*/  me_ctx; TYPE_2__* frames; } ;
struct TYPE_8__ {TYPE_1__* avf; } ;
struct TYPE_7__ {int width; int height; } ;
typedef  int /*<<< orphan*/  PixelWeights ;
typedef  int /*<<< orphan*/  PixelRefs ;
typedef  int /*<<< orphan*/  PixelMVS ;
typedef  TYPE_3__ MIContext ;
typedef  TYPE_4__ Block ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PIXELS (int,int,int) ; 
 int ALPHA_MAX ; 
 int FFMAX (int /*<<< orphan*/ ,int) ; 
 int FFMIN (int,int) ; 
 scalar_t__ MC_MODE_AOBMC ; 
 int UINT64_MAX ; 
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int get_sbad (int /*<<< orphan*/ *,int,int,int,int) ; 
 int** obmc_tab_linear ; 

__attribute__((used)) static void bilateral_obmc(MIContext *mi_ctx, Block *block, int mb_x, int mb_y, int alpha)
{
    int x, y;
    int width = mi_ctx->frames[0].avf->width;
    int height = mi_ctx->frames[0].avf->height;

    Block *nb;
    int nb_x, nb_y;
    uint64_t sbads[9];

    int mv_x = block->mvs[0][0] * 2;
    int mv_y = block->mvs[0][1] * 2;
    int start_x, start_y;
    int startc_x, startc_y, endc_x, endc_y;

    if (mi_ctx->mc_mode == MC_MODE_AOBMC)
        for (nb_y = FFMAX(0, mb_y - 1); nb_y < FFMIN(mb_y + 2, mi_ctx->b_height); nb_y++)
            for (nb_x = FFMAX(0, mb_x - 1); nb_x < FFMIN(mb_x + 2, mi_ctx->b_width); nb_x++) {
                int x_nb = nb_x << mi_ctx->log2_mb_size;
                int y_nb = nb_y << mi_ctx->log2_mb_size;

                if (nb_x - mb_x || nb_y - mb_y)
                    sbads[nb_x - mb_x + 1 + (nb_y - mb_y + 1) * 3] = get_sbad(&mi_ctx->me_ctx, x_nb, y_nb, x_nb + block->mvs[0][0], y_nb + block->mvs[0][1]);
            }

    start_x = (mb_x << mi_ctx->log2_mb_size) - mi_ctx->mb_size / 2;
    start_y = (mb_y << mi_ctx->log2_mb_size) - mi_ctx->mb_size / 2;

    startc_x = av_clip(start_x, 0, width - 1);
    startc_y = av_clip(start_y, 0, height - 1);
    endc_x = av_clip(start_x + (2 << mi_ctx->log2_mb_size), 0, width - 1);
    endc_y = av_clip(start_y + (2 << mi_ctx->log2_mb_size), 0, height - 1);

    for (y = startc_y; y < endc_y; y++) {
        int y_min = -y;
        int y_max = height - y - 1;
        for (x = startc_x; x < endc_x; x++) {
            int x_min = -x;
            int x_max = width - x - 1;
            int obmc_weight = obmc_tab_linear[4 - mi_ctx->log2_mb_size][(x - start_x) + ((y - start_y) << (mi_ctx->log2_mb_size + 1))];
            PixelMVS *pixel_mvs = &mi_ctx->pixel_mvs[x + y * width];
            PixelWeights *pixel_weights = &mi_ctx->pixel_weights[x + y * width];
            PixelRefs *pixel_refs = &mi_ctx->pixel_refs[x + y * width];

            if (mi_ctx->mc_mode == MC_MODE_AOBMC) {
                nb_x = (((x - start_x) >> (mi_ctx->log2_mb_size - 1)) * 2 - 3) / 2;
                nb_y = (((y - start_y) >> (mi_ctx->log2_mb_size - 1)) * 2 - 3) / 2;

                if (nb_x || nb_y) {
                    uint64_t sbad = sbads[nb_x + 1 + (nb_y + 1) * 3];
                    nb = &mi_ctx->int_blocks[mb_x + nb_x + (mb_y + nb_y) * mi_ctx->b_width];

                    if (sbad && sbad != UINT64_MAX && nb->sbad != UINT64_MAX) {
                        int phi = av_clip(ALPHA_MAX * nb->sbad / sbad, 0, ALPHA_MAX);
                        obmc_weight = obmc_weight * phi / ALPHA_MAX;
                    }
                }
            }

            ADD_PIXELS(obmc_weight, mv_x, mv_y);
        }
    }
}