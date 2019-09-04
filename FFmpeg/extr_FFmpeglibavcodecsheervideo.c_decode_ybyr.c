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
struct TYPE_9__ {int** data; size_t* linesize; } ;
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

__attribute__((used)) static void decode_ybyr(AVCodecContext *avctx, AVFrame *p, GetBitContext *gb)
{
    SheerVideoContext *s = avctx->priv_data;
    uint8_t *dst_y, *dst_u, *dst_v;
    int x, y;

    dst_y = p->data[0];
    dst_u = p->data[1];
    dst_v = p->data[2];

    if (get_bits1(gb)) {
        for (x = 0; x < avctx->width; x += 2) {
            dst_y[x    ] = get_bits(gb, 8);
            dst_u[x / 2] = get_bits(gb, 8) + 128;
            dst_y[x + 1] = get_bits(gb, 8);
            dst_v[x / 2] = get_bits(gb, 8) + 128;
        }
    } else {
        int pred[4] = { -128, 128, 128, 0 };

        for (x = 0; x < avctx->width; x += 2) {
            int y1, y2, u, v;

            y1 = get_vlc2(gb, s->vlc[0].table, s->vlc[0].bits, 2);
            u  = get_vlc2(gb, s->vlc[1].table, s->vlc[1].bits, 2);
            y2 = get_vlc2(gb, s->vlc[0].table, s->vlc[0].bits, 2);
            v  = get_vlc2(gb, s->vlc[1].table, s->vlc[1].bits, 2);

            dst_y[x    ] = pred[0] = (y1 + pred[0]) & 0xff;
            dst_u[x / 2] = pred[1] = (u  + pred[1]) & 0xff;
            dst_y[x + 1] = pred[0] = (y2 + pred[0]) & 0xff;
            dst_v[x / 2] = pred[2] = (v  + pred[2]) & 0xff;
        }
    }

    dst_y += p->linesize[0];
    dst_u += p->linesize[1];
    dst_v += p->linesize[2];

    for (y = 1; y < avctx->height; y++) {
        if (get_bits1(gb)) {
            for (x = 0; x < avctx->width; x += 2) {
                dst_y[x    ] = get_bits(gb, 8);
                dst_u[x / 2] = get_bits(gb, 8) + 128;
                dst_y[x + 1] = get_bits(gb, 8);
                dst_v[x / 2] = get_bits(gb, 8) + 128;
            }
        } else {
            int pred_TL[4], pred_L[4], pred_T[4];
            int y1, y2, u, v;

            pred_TL[0] = pred_L[0] = dst_y[-p->linesize[0]];
            pred_TL[1] = pred_L[1] = dst_u[-p->linesize[1]];
            pred_TL[2] = pred_L[2] = dst_v[-p->linesize[2]];

            for (x = 0; x < avctx->width; x += 2) {
                pred_T[0] = dst_y[-p->linesize[0] + x];
                pred_T[3] = dst_y[-p->linesize[0] + x + 1];
                pred_T[1] = dst_u[-p->linesize[1] + x / 2];
                pred_T[2] = dst_v[-p->linesize[2] + x / 2];

                y1 = get_vlc2(gb, s->vlc[0].table, s->vlc[0].bits, 2);
                u  = get_vlc2(gb, s->vlc[1].table, s->vlc[1].bits, 2);
                y2 = get_vlc2(gb, s->vlc[0].table, s->vlc[0].bits, 2);
                v  = get_vlc2(gb, s->vlc[1].table, s->vlc[1].bits, 2);

                dst_y[x    ] = pred_L[0] = (y1 + ((3 * (pred_T[0] + pred_L[0]) - 2 * pred_TL[0]) >> 2)) & 0xff;
                dst_u[x / 2] = pred_L[1] = (u + (((pred_L[1] - pred_TL[1]) >> 1) + pred_T[1])) & 0xff;
                dst_y[x + 1] = pred_L[0] = (y2 + ((3 * (pred_T[3] + pred_L[0]) - 2 * pred_T[0]) >> 2)) & 0xff;
                dst_v[x / 2] = pred_L[2] = (v + (((pred_L[2] - pred_TL[2]) >> 1) + pred_T[2])) & 0xff;

                pred_TL[0] = pred_T[3];
                pred_TL[1] = pred_T[1];
                pred_TL[2] = pred_T[2];
            }
        }

        dst_y += p->linesize[0];
        dst_u += p->linesize[1];
        dst_v += p->linesize[2];
    }
}