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
typedef  int uint8_t ;
struct TYPE_10__ {int width; int height; TYPE_2__* priv_data; } ;
struct TYPE_9__ {int** data; int* linesize; } ;
struct TYPE_8__ {TYPE_1__* vlc; } ;
struct TYPE_7__ {int /*<<< orphan*/  bits; int /*<<< orphan*/  table; } ;
typedef  TYPE_2__ SheerVideoContext ;
typedef  int /*<<< orphan*/  GetBitContext ;
typedef  TYPE_3__ AVFrame ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int get_bits (int /*<<< orphan*/ *,int) ; 
 scalar_t__ get_bits1 (int /*<<< orphan*/ *) ; 
 int get_vlc2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void decode_argb(AVCodecContext *avctx, AVFrame *p, GetBitContext *gb)
{
    SheerVideoContext *s = avctx->priv_data;
    uint8_t *dst;
    int x, y;

    dst = p->data[0];
    if (get_bits1(gb)) {
        for (x = 0; x < avctx->width; x++) {
            dst[x * 4 + 0] = get_bits(gb, 8);
            dst[x * 4 + 1] = get_bits(gb, 8);
            dst[x * 4 + 2] = get_bits(gb, 8);
            dst[x * 4 + 3] = get_bits(gb, 8);
        }
    } else {
        int pred[4] = { -128, -128, -128, -128 };

        for (x = 0; x < avctx->width; x++) {
            int a, r, g, b;

            a = get_vlc2(gb, s->vlc[1].table, s->vlc[1].bits, 2);
            r = get_vlc2(gb, s->vlc[0].table, s->vlc[0].bits, 2);
            g = get_vlc2(gb, s->vlc[1].table, s->vlc[1].bits, 2);
            b = get_vlc2(gb, s->vlc[1].table, s->vlc[1].bits, 2);

            dst[4 * x + 0] = pred[0] = (a + pred[0]) & 0xff;
            dst[4 * x + 1] = pred[1] = (r + pred[1]) & 0xff;
            dst[4 * x + 2] = pred[2] = (r + g + pred[2]) & 0xff;
            dst[4 * x + 3] = pred[3] = (r + g + b + pred[3]) & 0xff;
        }
    }

    dst += p->linesize[0];
    for (y = 1; y < avctx->height; y++) {
        if (get_bits1(gb)) {
            for (x = 0; x < avctx->width; x++) {
                dst[x * 4 + 0] = get_bits(gb, 8);
                dst[x * 4 + 1] = get_bits(gb, 8);
                dst[x * 4 + 2] = get_bits(gb, 8);
                dst[x * 4 + 3] = get_bits(gb, 8);
            }
        } else {
            int pred_TL[4], pred_L[4], pred_T[4];
            int a, r, g, b;

            pred_TL[0] = pred_L[0] = dst[-p->linesize[0] + 0];
            pred_TL[1] = pred_L[1] = dst[-p->linesize[0] + 1];
            pred_TL[2] = pred_L[2] = dst[-p->linesize[0] + 2];
            pred_TL[3] = pred_L[3] = dst[-p->linesize[0] + 3];

            for (x = 0; x < avctx->width; x++) {
                pred_T[0] = dst[-p->linesize[0] + 4 * x + 0];
                pred_T[1] = dst[-p->linesize[0] + 4 * x + 1];
                pred_T[2] = dst[-p->linesize[0] + 4 * x + 2];
                pred_T[3] = dst[-p->linesize[0] + 4 * x + 3];

                a = get_vlc2(gb, s->vlc[1].table, s->vlc[1].bits, 2);
                r = get_vlc2(gb, s->vlc[0].table, s->vlc[0].bits, 2);
                g = get_vlc2(gb, s->vlc[1].table, s->vlc[1].bits, 2);
                b = get_vlc2(gb, s->vlc[1].table, s->vlc[1].bits, 2);

                dst[4 * x + 0] = pred_L[0] = (a + ((3 * (pred_T[0] + pred_L[0]) - 2 * pred_TL[0]) >> 2)) & 0xff;
                dst[4 * x + 1] = pred_L[1] = (r + ((3 * (pred_T[1] + pred_L[1]) - 2 * pred_TL[1]) >> 2)) & 0xff;
                dst[4 * x + 2] = pred_L[2] = (r + g + ((3 * (pred_T[2] + pred_L[2]) - 2 * pred_TL[2]) >> 2)) & 0xff;
                dst[4 * x + 3] = pred_L[3] = (r + g + b + ((3 * (pred_T[3] + pred_L[3]) - 2 * pred_TL[3]) >> 2)) & 0xff;

                pred_TL[0] = pred_T[0];
                pred_TL[1] = pred_T[1];
                pred_TL[2] = pred_T[2];
                pred_TL[3] = pred_T[3];
            }
        }
        dst += p->linesize[0];
    }
}