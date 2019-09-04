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
struct TYPE_7__ {int* linesize; int /*<<< orphan*/ ** data; } ;
struct TYPE_6__ {int tex_size; int (* tex_fun ) (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ HapContext ;
typedef  TYPE_2__ AVFrame ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR_BUFFER_TOO_SMALL ; 
 int stub1 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int compress_texture(AVCodecContext *avctx, uint8_t *out, int out_length, const AVFrame *f)
{
    HapContext *ctx = avctx->priv_data;
    int i, j;

    if (ctx->tex_size > out_length)
        return AVERROR_BUFFER_TOO_SMALL;

    for (j = 0; j < avctx->height; j += 4) {
        for (i = 0; i < avctx->width; i += 4) {
            uint8_t *p = f->data[0] + i * 4 + j * f->linesize[0];
            const int step = ctx->tex_fun(out, f->linesize[0], p);
            out += step;
        }
    }

    return 0;
}