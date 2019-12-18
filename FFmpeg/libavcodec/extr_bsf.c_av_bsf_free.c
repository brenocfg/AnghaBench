#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  par_out; int /*<<< orphan*/  par_in; struct TYPE_8__* priv_data; struct TYPE_8__* internal; int /*<<< orphan*/  buffer_pkt; TYPE_1__* filter; } ;
struct TYPE_7__ {scalar_t__ priv_class; int /*<<< orphan*/  (* close ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ AVBSFContext ;

/* Variables and functions */
 int /*<<< orphan*/  av_freep (TYPE_2__**) ; 
 int /*<<< orphan*/  av_opt_free (TYPE_2__*) ; 
 int /*<<< orphan*/  av_packet_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avcodec_parameters_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

void av_bsf_free(AVBSFContext **pctx)
{
    AVBSFContext *ctx;

    if (!pctx || !*pctx)
        return;
    ctx = *pctx;

    if (ctx->filter->close)
        ctx->filter->close(ctx);
    if (ctx->filter->priv_class && ctx->priv_data)
        av_opt_free(ctx->priv_data);

    av_opt_free(ctx);

    if (ctx->internal)
        av_packet_free(&ctx->internal->buffer_pkt);
    av_freep(&ctx->internal);
    av_freep(&ctx->priv_data);

    avcodec_parameters_free(&ctx->par_in);
    avcodec_parameters_free(&ctx->par_out);

    av_freep(pctx);
}