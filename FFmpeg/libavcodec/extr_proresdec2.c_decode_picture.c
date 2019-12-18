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
struct TYPE_10__ {int /*<<< orphan*/  (* execute2 ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ;TYPE_3__* priv_data; } ;
struct TYPE_9__ {int slice_count; TYPE_2__* slices; TYPE_1__* frame; } ;
struct TYPE_8__ {scalar_t__ ret; } ;
struct TYPE_7__ {int /*<<< orphan*/  decode_error_flags; } ;
typedef  TYPE_3__ ProresContext ;
typedef  TYPE_4__ AVCodecContext ;

/* Variables and functions */
 int /*<<< orphan*/  FF_DECODE_ERROR_INVALID_BITSTREAM ; 
 int /*<<< orphan*/  decode_slice_thread ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int decode_picture(AVCodecContext *avctx)
{
    ProresContext *ctx = avctx->priv_data;
    int i;
    int error = 0;

    avctx->execute2(avctx, decode_slice_thread, NULL, NULL, ctx->slice_count);

    for (i = 0; i < ctx->slice_count; i++)
        error += ctx->slices[i].ret < 0;

    if (error)
        ctx->frame->decode_error_flags = FF_DECODE_ERROR_INVALID_BITSTREAM;
    if (error < ctx->slice_count)
        return 0;

    return ctx->slices[0].ret;
}