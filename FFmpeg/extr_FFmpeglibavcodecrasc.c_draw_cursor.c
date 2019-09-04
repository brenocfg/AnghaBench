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
struct TYPE_7__ {scalar_t__ width; scalar_t__ height; scalar_t__ pix_fmt; TYPE_2__* priv_data; } ;
struct TYPE_6__ {int* cursor; scalar_t__ cursor_x; scalar_t__ cursor_y; int cursor_w; scalar_t__ cursor_h; TYPE_1__* frame; } ;
struct TYPE_5__ {int** data; int* linesize; } ;
typedef  TYPE_2__ RASCContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_BGR0 ; 
 scalar_t__ AV_PIX_FMT_PAL8 ; 
 scalar_t__ AV_PIX_FMT_RGB555LE ; 
 int /*<<< orphan*/  AV_WL16 (int*,int) ; 
 int FFABS (int) ; 
 int INT_MAX ; 

__attribute__((used)) static void draw_cursor(AVCodecContext *avctx)
{
    RASCContext *s = avctx->priv_data;
    uint8_t *dst, *pal;

    if (!s->cursor)
        return;

    if (s->cursor_x >= avctx->width || s->cursor_y >= avctx->height)
        return;

    if (s->cursor_x + s->cursor_w > avctx->width ||
        s->cursor_y + s->cursor_h > avctx->height)
        return;

    if (avctx->pix_fmt == AV_PIX_FMT_PAL8) {
        pal = s->frame->data[1];
        for (int i = 0; i < s->cursor_h; i++) {
            for (int j = 0; j < s->cursor_w; j++) {
                int cr = s->cursor[3 * s->cursor_w * (s->cursor_h - i - 1) + 3 * j + 0];
                int cg = s->cursor[3 * s->cursor_w * (s->cursor_h - i - 1) + 3 * j + 1];
                int cb = s->cursor[3 * s->cursor_w * (s->cursor_h - i - 1) + 3 * j + 2];
                int best = INT_MAX;
                int index = 0;
                int dist;

                if (cr == s->cursor[0] && cg == s->cursor[1] && cb == s->cursor[2])
                    continue;

                dst = s->frame->data[0] + s->frame->linesize[0] * (s->cursor_y + i) + (s->cursor_x + j);
                for (int k = 0; k < 256; k++) {
                    int pr = pal[k * 4 + 0];
                    int pg = pal[k * 4 + 1];
                    int pb = pal[k * 4 + 2];

                    dist = FFABS(cr - pr) + FFABS(cg - pg) + FFABS(cb - pb);
                    if (dist < best) {
                        best = dist;
                        index = k;
                    }
                }
                dst[0] = index;
            }
        }
    } else if (avctx->pix_fmt == AV_PIX_FMT_RGB555LE) {
        for (int i = 0; i < s->cursor_h; i++) {
            for (int j = 0; j < s->cursor_w; j++) {
                int cr = s->cursor[3 * s->cursor_w * (s->cursor_h - i - 1) + 3 * j + 0];
                int cg = s->cursor[3 * s->cursor_w * (s->cursor_h - i - 1) + 3 * j + 1];
                int cb = s->cursor[3 * s->cursor_w * (s->cursor_h - i - 1) + 3 * j + 2];

                if (cr == s->cursor[0] && cg == s->cursor[1] && cb == s->cursor[2])
                    continue;

                cr >>= 3; cg >>=3; cb >>= 3;
                dst = s->frame->data[0] + s->frame->linesize[0] * (s->cursor_y + i) + 2 * (s->cursor_x + j);
                AV_WL16(dst, cr | cg << 5 | cb << 10);
            }
        }
    } else if (avctx->pix_fmt == AV_PIX_FMT_BGR0) {
        for (int i = 0; i < s->cursor_h; i++) {
            for (int j = 0; j < s->cursor_w; j++) {
                int cr = s->cursor[3 * s->cursor_w * (s->cursor_h - i - 1) + 3 * j + 0];
                int cg = s->cursor[3 * s->cursor_w * (s->cursor_h - i - 1) + 3 * j + 1];
                int cb = s->cursor[3 * s->cursor_w * (s->cursor_h - i - 1) + 3 * j + 2];

                if (cr == s->cursor[0] && cg == s->cursor[1] && cb == s->cursor[2])
                    continue;

                dst = s->frame->data[0] + s->frame->linesize[0] * (s->cursor_y + i) + 4 * (s->cursor_x + j);
                dst[0] = cb;
                dst[1] = cg;
                dst[2] = cr;
            }
        }
    }
}