#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_8__ {int height; int width; TYPE_1__* priv_data; } ;
struct TYPE_7__ {int /*<<< orphan*/ * linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_6__ {int bpp; } ;
typedef  TYPE_1__ RASCContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void clear_plane(AVCodecContext *avctx, AVFrame *frame)
{
    RASCContext *s = avctx->priv_data;
    uint8_t *dst = frame->data[0];

    for (int y = 0; y < avctx->height; y++) {
        memset(dst, 0, avctx->width * s->bpp);
        dst += frame->linesize[0];
    }
}