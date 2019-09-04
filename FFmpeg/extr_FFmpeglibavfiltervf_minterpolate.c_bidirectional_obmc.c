#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int b_height; int b_width; int log2_mb_size; int mb_size; TYPE_4__* pixel_refs; int /*<<< orphan*/ * pixel_weights; int /*<<< orphan*/ * pixel_mvs; TYPE_3__* frames; } ;
struct TYPE_10__ {scalar_t__ nb; } ;
struct TYPE_9__ {TYPE_2__* blocks; TYPE_1__* avf; } ;
struct TYPE_8__ {int** mvs; } ;
struct TYPE_7__ {int width; int height; } ;
typedef  int /*<<< orphan*/  PixelWeights ;
typedef  TYPE_4__ PixelRefs ;
typedef  int /*<<< orphan*/  PixelMVS ;
typedef  TYPE_5__ MIContext ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PIXELS (int,int,int) ; 
 int ALPHA_MAX ; 
 int av_clip (int,int /*<<< orphan*/ ,int) ; 
 int** obmc_tab_linear ; 

__attribute__((used)) static void bidirectional_obmc(MIContext *mi_ctx, int alpha)
{
    int x, y;
    int width = mi_ctx->frames[0].avf->width;
    int height = mi_ctx->frames[0].avf->height;
    int mb_y, mb_x, dir;

    for (y = 0; y < height; y++)
        for (x = 0; x < width; x++)
            mi_ctx->pixel_refs[x + y * width].nb = 0;

    for (dir = 0; dir < 2; dir++)
        for (mb_y = 0; mb_y < mi_ctx->b_height; mb_y++)
            for (mb_x = 0; mb_x < mi_ctx->b_width; mb_x++) {
                int a = dir ? alpha : (ALPHA_MAX - alpha);
                int mv_x = mi_ctx->frames[2 - dir].blocks[mb_x + mb_y * mi_ctx->b_width].mvs[dir][0];
                int mv_y = mi_ctx->frames[2 - dir].blocks[mb_x + mb_y * mi_ctx->b_width].mvs[dir][1];
                int start_x, start_y;
                int startc_x, startc_y, endc_x, endc_y;

                start_x = (mb_x << mi_ctx->log2_mb_size) - mi_ctx->mb_size / 2 + mv_x * a / ALPHA_MAX;
                start_y = (mb_y << mi_ctx->log2_mb_size) - mi_ctx->mb_size / 2 + mv_y * a / ALPHA_MAX;

                startc_x = av_clip(start_x, 0, width - 1);
                startc_y = av_clip(start_y, 0, height - 1);
                endc_x = av_clip(start_x + (2 << mi_ctx->log2_mb_size), 0, width - 1);
                endc_y = av_clip(start_y + (2 << mi_ctx->log2_mb_size), 0, height - 1);

                if (dir) {
                    mv_x = -mv_x;
                    mv_y = -mv_y;
                }

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

                        ADD_PIXELS(obmc_weight, mv_x, mv_y);
                    }
                }
            }
}