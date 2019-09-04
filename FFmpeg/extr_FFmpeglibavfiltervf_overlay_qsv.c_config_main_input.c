#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ PixelAlphaEnable; scalar_t__ GlobalAlphaEnable; int /*<<< orphan*/  DstH; int /*<<< orphan*/  DstW; scalar_t__ DstY; scalar_t__ DstX; } ;
typedef  TYPE_2__ mfxVPPCompInputStream ;
struct TYPE_13__ {TYPE_3__* priv; } ;
struct TYPE_12__ {int /*<<< orphan*/  h; int /*<<< orphan*/  w; int /*<<< orphan*/  format; TYPE_5__* dst; } ;
struct TYPE_9__ {TYPE_2__* InputStream; } ;
struct TYPE_11__ {int /*<<< orphan*/ * var_values; TYPE_1__ comp_conf; } ;
typedef  TYPE_3__ QSVOverlayContext ;
typedef  TYPE_4__ AVFilterLink ;
typedef  TYPE_5__ AVFilterContext ;

/* Variables and functions */
 int /*<<< orphan*/  AV_LOG_DEBUG ; 
 int /*<<< orphan*/  FF_INLINK_IDX (TYPE_4__*) ; 
 size_t VAR_MAIN_iH ; 
 size_t VAR_MAIN_iW ; 
 size_t VAR_MH ; 
 size_t VAR_MW ; 
 int /*<<< orphan*/  av_get_pix_fmt_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  av_log (TYPE_5__*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int config_main_input(AVFilterLink *inlink)
{
    AVFilterContext      *ctx = inlink->dst;
    QSVOverlayContext    *vpp = ctx->priv;
    mfxVPPCompInputStream *st = &vpp->comp_conf.InputStream[0];

    av_log(ctx, AV_LOG_DEBUG, "Input[%d] is of %s.\n", FF_INLINK_IDX(inlink),
           av_get_pix_fmt_name(inlink->format));

    vpp->var_values[VAR_MAIN_iW] =
    vpp->var_values[VAR_MW]      = inlink->w;
    vpp->var_values[VAR_MAIN_iH] =
    vpp->var_values[VAR_MH]      = inlink->h;

    st->DstX              = 0;
    st->DstY              = 0;
    st->DstW              = inlink->w;
    st->DstH              = inlink->h;
    st->GlobalAlphaEnable = 0;
    st->PixelAlphaEnable  = 0;

    return 0;
}