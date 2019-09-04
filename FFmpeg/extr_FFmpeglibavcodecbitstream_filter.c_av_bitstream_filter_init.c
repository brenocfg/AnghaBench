#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ctx; struct TYPE_6__* priv_data; int /*<<< orphan*/  const* filter; } ;
typedef  TYPE_1__ BSFCompatContext ;
typedef  TYPE_1__ AVBitStreamFilterContext ;
typedef  int /*<<< orphan*/  AVBitStreamFilter ;

/* Variables and functions */
 int /*<<< orphan*/  av_bsf_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * av_bsf_get_by_name (char const*) ; 
 int /*<<< orphan*/  av_freep (TYPE_1__**) ; 
 TYPE_1__* av_mallocz (int) ; 

AVBitStreamFilterContext *av_bitstream_filter_init(const char *name)
{
    AVBitStreamFilterContext *ctx = NULL;
    BSFCompatContext         *priv = NULL;
    const AVBitStreamFilter *bsf;

    bsf = av_bsf_get_by_name(name);
    if (!bsf)
        return NULL;

    ctx = av_mallocz(sizeof(*ctx));
    if (!ctx)
        return NULL;

    priv = av_mallocz(sizeof(*priv));
    if (!priv)
        goto fail;


    ctx->filter    = bsf;
    ctx->priv_data = priv;

    return ctx;

fail:
    if (priv)
        av_bsf_free(&priv->ctx);
    av_freep(&priv);
    av_freep(&ctx);
    return NULL;
}