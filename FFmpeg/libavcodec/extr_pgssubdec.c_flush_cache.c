#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_4__* priv_data; } ;
struct TYPE_9__ {scalar_t__ count; } ;
struct TYPE_8__ {int count; TYPE_1__* object; } ;
struct TYPE_10__ {TYPE_3__ palettes; TYPE_2__ objects; } ;
struct TYPE_7__ {scalar_t__ rle_remaining_len; scalar_t__ rle_buffer_size; int /*<<< orphan*/  rle; } ;
typedef  TYPE_4__ PGSSubContext ;
typedef  TYPE_5__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void flush_cache(AVCodecContext *avctx)
{
    PGSSubContext *ctx = avctx->priv_data;
    int i;

    for (i = 0; i < ctx->objects.count; i++) {
        av_freep(&ctx->objects.object[i].rle);
        ctx->objects.object[i].rle_buffer_size  = 0;
        ctx->objects.object[i].rle_remaining_len  = 0;
    }
    ctx->objects.count = 0;
    ctx->palettes.count = 0;
}