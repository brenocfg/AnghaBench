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
struct TYPE_10__ {int height; int width; TYPE_2__* priv_data; } ;
struct TYPE_9__ {int** data; int /*<<< orphan*/ * linesize; } ;
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

__attribute__((used)) static void decode_c82i(AVCodecContext *avctx, AVFrame *p, GetBitContext *gb)
{
    SheerVideoContext *s = avctx->priv_data;
    uint8_t *dst_y, *dst_u, *dst_v, *dst_a;
    int x, y;

    dst_y = p->data[0];
    dst_u = p->data[1];
    dst_v = p->data[2];
    dst_a = p->data[3];

    for (y = 0; y < avctx->height; y += 1) {
        if (get_bits1(gb)) {
            for (x = 0; x < avctx->width; x += 2) {
                dst_a[x    ] = get_bits(gb, 8);
                dst_y[x    ] = get_bits(gb, 8);
                dst_u[x / 2] = get_bits(gb, 8);
                dst_a[x + 1] = get_bits(gb, 8);
                dst_y[x + 1] = get_bits(gb, 8);
                dst_v[x / 2] = get_bits(gb, 8);
            }
        } else {
            int pred[4] = { 125, -128, -128, 125 };

            for (x = 0; x < avctx->width; x += 2) {
                int y1, y2, u, v, a1, a2;

                a1 = get_vlc2(gb, s->vlc[1].table, s->vlc[1].bits, 2);
                y1 = get_vlc2(gb, s->vlc[0].table, s->vlc[0].bits, 2);
                u  = get_vlc2(gb, s->vlc[1].table, s->vlc[1].bits, 2);
                a2 = get_vlc2(gb, s->vlc[1].table, s->vlc[1].bits, 2);
                y2 = get_vlc2(gb, s->vlc[0].table, s->vlc[0].bits, 2);
                v  = get_vlc2(gb, s->vlc[1].table, s->vlc[1].bits, 2);

                dst_y[x    ] = pred[0] = (y1 + pred[0]) & 0xff;
                dst_y[x + 1] = pred[0] = (y2 + pred[0]) & 0xff;
                dst_u[x / 2] = pred[1] = (u  + pred[1]) & 0xff;
                dst_v[x / 2] = pred[2] = (v  + pred[2]) & 0xff;
                dst_a[x    ] = pred[3] = (a1 + pred[3]) & 0xff;
                dst_a[x + 1] = pred[3] = (a2 + pred[3]) & 0xff;
            }
        }

        dst_y += p->linesize[0];
        dst_u += p->linesize[1];
        dst_v += p->linesize[2];
        dst_a += p->linesize[3];
    }
}