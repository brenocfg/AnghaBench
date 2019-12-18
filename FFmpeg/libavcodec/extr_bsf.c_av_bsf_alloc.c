#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* priv_data; TYPE_1__* internal; void* par_out; void* par_in; TYPE_2__ const* filter; int /*<<< orphan*/ * av_class; } ;
struct TYPE_9__ {int priv_data_size; int /*<<< orphan*/ * priv_class; } ;
struct TYPE_8__ {int /*<<< orphan*/  buffer_pkt; } ;
typedef  int /*<<< orphan*/  AVClass ;
typedef  TYPE_2__ AVBitStreamFilter ;
typedef  TYPE_3__ AVBSFContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  av_bsf_free (TYPE_3__**) ; 
 void* av_mallocz (int) ; 
 int /*<<< orphan*/  av_opt_set_defaults (TYPE_3__*) ; 
 int /*<<< orphan*/  av_packet_alloc () ; 
 void* avcodec_parameters_alloc () ; 
 int /*<<< orphan*/  bsf_class ; 

int av_bsf_alloc(const AVBitStreamFilter *filter, AVBSFContext **pctx)
{
    AVBSFContext *ctx;
    int ret;

    ctx = av_mallocz(sizeof(*ctx));
    if (!ctx)
        return AVERROR(ENOMEM);

    ctx->av_class = &bsf_class;
    ctx->filter   = filter;

    ctx->par_in  = avcodec_parameters_alloc();
    ctx->par_out = avcodec_parameters_alloc();
    if (!ctx->par_in || !ctx->par_out) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    ctx->internal = av_mallocz(sizeof(*ctx->internal));
    if (!ctx->internal) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    ctx->internal->buffer_pkt = av_packet_alloc();
    if (!ctx->internal->buffer_pkt) {
        ret = AVERROR(ENOMEM);
        goto fail;
    }

    av_opt_set_defaults(ctx);

    /* allocate priv data and init private options */
    if (filter->priv_data_size) {
        ctx->priv_data = av_mallocz(filter->priv_data_size);
        if (!ctx->priv_data) {
            ret = AVERROR(ENOMEM);
            goto fail;
        }
        if (filter->priv_class) {
            *(const AVClass **)ctx->priv_data = filter->priv_class;
            av_opt_set_defaults(ctx->priv_data);
        }
    }

    *pctx = ctx;
    return 0;
fail:
    av_bsf_free(&ctx);
    return ret;
}