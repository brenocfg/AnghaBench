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
struct TYPE_10__ {int** mvs; scalar_t__ sb; struct TYPE_10__* subs; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pixel_refs; int /*<<< orphan*/ * pixel_weights; int /*<<< orphan*/ * pixel_mvs; TYPE_2__* frames; } ;
struct TYPE_8__ {TYPE_1__* avf; } ;
struct TYPE_7__ {int width; int height; } ;
typedef  int /*<<< orphan*/  PixelWeights ;
typedef  int /*<<< orphan*/  PixelRefs ;
typedef  int /*<<< orphan*/  PixelMVS ;
typedef  TYPE_3__ MIContext ;
typedef  TYPE_4__ Block ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_PIXELS (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  PX_WEIGHT_MAX ; 

__attribute__((used)) static void var_size_bmc(MIContext *mi_ctx, Block *block, int x_mb, int y_mb, int n, int alpha)
{
    int sb_x, sb_y;
    int width = mi_ctx->frames[0].avf->width;
    int height = mi_ctx->frames[0].avf->height;

    for (sb_y = 0; sb_y < 2; sb_y++)
        for (sb_x = 0; sb_x < 2; sb_x++) {
            Block *sb = &block->subs[sb_x + sb_y * 2];

            if (sb->sb)
                var_size_bmc(mi_ctx, sb, x_mb + (sb_x << (n - 1)), y_mb + (sb_y << (n - 1)), n - 1, alpha);
            else {
                int x, y;
                int mv_x = sb->mvs[0][0] * 2;
                int mv_y = sb->mvs[0][1] * 2;

                int start_x = x_mb + (sb_x << (n - 1));
                int start_y = y_mb + (sb_y << (n - 1));
                int end_x = start_x + (1 << (n - 1));
                int end_y = start_y + (1 << (n - 1));

                for (y = start_y; y < end_y; y++)  {
                    int y_min = -y;
                    int y_max = height - y - 1;
                    for (x = start_x; x < end_x; x++) {
                        int x_min = -x;
                        int x_max = width - x - 1;
                        PixelMVS *pixel_mvs = &mi_ctx->pixel_mvs[x + y * width];
                        PixelWeights *pixel_weights = &mi_ctx->pixel_weights[x + y * width];
                        PixelRefs *pixel_refs = &mi_ctx->pixel_refs[x + y * width];

                        ADD_PIXELS(PX_WEIGHT_MAX, mv_x, mv_y);
                    }
                }
            }
        }
}