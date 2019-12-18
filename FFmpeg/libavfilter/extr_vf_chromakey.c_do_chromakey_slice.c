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
typedef  int /*<<< orphan*/  v ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  u ;
struct TYPE_9__ {TYPE_1__* priv; } ;
struct TYPE_8__ {int height; int width; int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_7__ {int /*<<< orphan*/  vsub_log2; int /*<<< orphan*/  hsub_log2; int /*<<< orphan*/ * chromakey_uv; } ;
typedef  TYPE_1__ ChromakeyContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  do_chromakey_pixel (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_pixel_uv (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int do_chromakey_slice(AVFilterContext *avctx, void *arg, int jobnr, int nb_jobs)
{
    AVFrame *frame = arg;

    const int slice_start = (frame->height * jobnr) / nb_jobs;
    const int slice_end = (frame->height * (jobnr + 1)) / nb_jobs;

    ChromakeyContext *ctx = avctx->priv;

    int x, y, xo, yo;
    uint8_t u[9], v[9];

    memset(u, ctx->chromakey_uv[0], sizeof(u));
    memset(v, ctx->chromakey_uv[1], sizeof(v));

    for (y = slice_start; y < slice_end; ++y) {
        for (x = 0; x < frame->width; ++x) {
            for (yo = 0; yo < 3; ++yo) {
                for (xo = 0; xo < 3; ++xo) {
                    get_pixel_uv(frame, ctx->hsub_log2, ctx->vsub_log2, x + xo - 1, y + yo - 1, &u[yo * 3 + xo], &v[yo * 3 + xo]);
                }
            }

            frame->data[3][frame->linesize[3] * y + x] = do_chromakey_pixel(ctx, u, v);
        }
    }

    return 0;
}