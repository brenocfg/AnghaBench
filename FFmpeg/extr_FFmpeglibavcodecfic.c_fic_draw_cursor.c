#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_7__ {scalar_t__ width; scalar_t__ height; TYPE_2__* priv_data; } ;
struct TYPE_6__ {int* cursor_buf; TYPE_1__* final_frame; } ;
struct TYPE_5__ {int** data; int* linesize; } ;
typedef  TYPE_2__ FICContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int FFMIN (int,scalar_t__) ; 
 int /*<<< orphan*/  fic_alpha_blend (int*,int*,int,int*) ; 

__attribute__((used)) static void fic_draw_cursor(AVCodecContext *avctx, int cur_x, int cur_y)
{
    FICContext *ctx = avctx->priv_data;
    uint8_t *ptr    = ctx->cursor_buf;
    uint8_t *dstptr[3];
    uint8_t planes[4][1024];
    uint8_t chroma[3][256];
    int i, j, p;

    /* Convert to YUVA444. */
    for (i = 0; i < 1024; i++) {
        planes[0][i] = (( 25 * ptr[0] + 129 * ptr[1] +  66 * ptr[2]) / 255) + 16;
        planes[1][i] = ((-38 * ptr[0] + 112 * ptr[1] + -74 * ptr[2]) / 255) + 128;
        planes[2][i] = ((-18 * ptr[0] + 112 * ptr[1] + -94 * ptr[2]) / 255) + 128;
        planes[3][i] = ptr[3];

        ptr += 4;
    }

    /* Subsample chroma. */
    for (i = 0; i < 32; i += 2)
        for (j = 0; j < 32; j += 2)
            for (p = 0; p < 3; p++)
                chroma[p][16 * (i / 2) + j / 2] = (planes[p + 1][32 *  i      + j    ] +
                                                   planes[p + 1][32 *  i      + j + 1] +
                                                   planes[p + 1][32 * (i + 1) + j    ] +
                                                   planes[p + 1][32 * (i + 1) + j + 1]) / 4;

    /* Seek to x/y pos of cursor. */
    for (i = 0; i < 3; i++)
        dstptr[i] = ctx->final_frame->data[i]                        +
                    (ctx->final_frame->linesize[i] * (cur_y >> !!i)) +
                    (cur_x >> !!i) + !!i;

    /* Copy. */
    for (i = 0; i < FFMIN(32, avctx->height - cur_y) - 1; i += 2) {
        int lsize = FFMIN(32, avctx->width - cur_x);
        int csize = lsize / 2;

        fic_alpha_blend(dstptr[0],
                        planes[0] + i * 32, lsize, planes[3] + i * 32);
        fic_alpha_blend(dstptr[0] + ctx->final_frame->linesize[0],
                        planes[0] + (i + 1) * 32, lsize, planes[3] + (i + 1) * 32);
        fic_alpha_blend(dstptr[1],
                        chroma[0] + (i / 2) * 16, csize, chroma[2] + (i / 2) * 16);
        fic_alpha_blend(dstptr[2],
                        chroma[1] + (i / 2) * 16, csize, chroma[2] + (i / 2) * 16);

        dstptr[0] += ctx->final_frame->linesize[0] * 2;
        dstptr[1] += ctx->final_frame->linesize[1];
        dstptr[2] += ctx->final_frame->linesize[2];
    }
}