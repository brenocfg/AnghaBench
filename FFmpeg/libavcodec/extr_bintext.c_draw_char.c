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
struct TYPE_6__ {int y; int font_height; scalar_t__ x; int /*<<< orphan*/  font; TYPE_1__* frame; } ;
typedef  TYPE_2__ XbinContext ;
struct TYPE_7__ {int height; scalar_t__ width; TYPE_2__* priv_data; } ;
struct TYPE_5__ {scalar_t__* data; int* linesize; } ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 scalar_t__ FONT_WIDTH ; 
 int /*<<< orphan*/  ff_draw_pc_font (scalar_t__,int,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static void draw_char(AVCodecContext *avctx, int c, int a)
{
    XbinContext *s = avctx->priv_data;
    if (s->y > avctx->height - s->font_height)
        return;
    ff_draw_pc_font(s->frame->data[0] + s->y * s->frame->linesize[0] + s->x,
                    s->frame->linesize[0], s->font, s->font_height, c,
                    a & 0x0F, a >> 4);
    s->x += FONT_WIDTH;
    if (s->x > avctx->width - FONT_WIDTH) {
        s->x = 0;
        s->y += s->font_height;
    }
}