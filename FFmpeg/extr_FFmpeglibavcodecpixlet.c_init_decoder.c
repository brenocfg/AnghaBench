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
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_7__ {TYPE_2__* priv_data; } ;
struct TYPE_6__ {unsigned int h; unsigned int w; int levels; TYPE_1__** band; void* prediction; void** filter; } ;
struct TYPE_5__ {unsigned int width; unsigned int height; unsigned int size; unsigned int x; unsigned int y; } ;
typedef  TYPE_2__ PixletContext ;
typedef  TYPE_3__ AVCodecContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 unsigned int FFMAX (unsigned int,unsigned int) ; 
 unsigned int NB_LEVELS ; 
 void* av_malloc_array (unsigned int,int) ; 

__attribute__((used)) static int init_decoder(AVCodecContext *avctx)
{
    PixletContext *ctx = avctx->priv_data;
    int i, plane;

    ctx->filter[0]  = av_malloc_array(ctx->h, sizeof(int16_t));
    ctx->filter[1]  = av_malloc_array(FFMAX(ctx->h, ctx->w) + 16, sizeof(int16_t));
    ctx->prediction = av_malloc_array((ctx->w >> NB_LEVELS), sizeof(int16_t));
    if (!ctx->filter[0] || !ctx->filter[1] || !ctx->prediction)
        return AVERROR(ENOMEM);

    for (plane = 0; plane < 3; plane++) {
        unsigned shift = plane > 0;
        unsigned w     = ctx->w >> shift;
        unsigned h     = ctx->h >> shift;

        ctx->band[plane][0].width  =  w >> NB_LEVELS;
        ctx->band[plane][0].height =  h >> NB_LEVELS;
        ctx->band[plane][0].size   = (w >> NB_LEVELS) * (h >> NB_LEVELS);

        for (i = 0; i < NB_LEVELS * 3; i++) {
            unsigned scale = ctx->levels - (i / 3);

            ctx->band[plane][i + 1].width  =  w >> scale;
            ctx->band[plane][i + 1].height =  h >> scale;
            ctx->band[plane][i + 1].size   = (w >> scale) * (h >> scale);

            ctx->band[plane][i + 1].x = (w >> scale) * (((i + 1) % 3) != 2);
            ctx->band[plane][i + 1].y = (h >> scale) * (((i + 1) % 3) != 1);
        }
    }

    return 0;
}