#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VScalerContext ;
struct TYPE_7__ {int /*<<< orphan*/  use_mmx_vfilter; int /*<<< orphan*/  yuv2anyX; scalar_t__ yuv2packedX; int /*<<< orphan*/  yuv2packed2; int /*<<< orphan*/  yuv2packed1; int /*<<< orphan*/  yuv2nv12cX; int /*<<< orphan*/  yuv2planeX; int /*<<< orphan*/  yuv2plane1; int /*<<< orphan*/  needAlpha; int /*<<< orphan*/  dstFormat; } ;
struct TYPE_6__ {int /*<<< orphan*/  alpha; int /*<<< orphan*/ * dst; int /*<<< orphan*/ * src; int /*<<< orphan*/ * instance; int /*<<< orphan*/  process; } ;
typedef  int /*<<< orphan*/  SwsSlice ;
typedef  TYPE_1__ SwsFilterDescriptor ;
typedef  TYPE_2__ SwsContext ;

/* Variables and functions */
 int AVERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  any_vscale ; 
 int /*<<< orphan*/ * av_mallocz (int) ; 
 int /*<<< orphan*/ * av_mallocz_array (int,int) ; 
 int /*<<< orphan*/  chr_planar_vscale ; 
 int /*<<< orphan*/  ff_init_vscale_pfn (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isALPHA (int /*<<< orphan*/ ) ; 
 scalar_t__ isGray (int /*<<< orphan*/ ) ; 
 scalar_t__ isPlanarYUV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lum_planar_vscale ; 
 int /*<<< orphan*/  packed_vscale ; 

int ff_init_vscale(SwsContext *c, SwsFilterDescriptor *desc, SwsSlice *src, SwsSlice *dst)
{
    VScalerContext *lumCtx = NULL;
    VScalerContext *chrCtx = NULL;

    if (isPlanarYUV(c->dstFormat) || (isGray(c->dstFormat) && !isALPHA(c->dstFormat))) {
        lumCtx = av_mallocz(sizeof(VScalerContext));
        if (!lumCtx)
            return AVERROR(ENOMEM);


        desc[0].process = lum_planar_vscale;
        desc[0].instance = lumCtx;
        desc[0].src = src;
        desc[0].dst = dst;
        desc[0].alpha = c->needAlpha;

        if (!isGray(c->dstFormat)) {
            chrCtx = av_mallocz(sizeof(VScalerContext));
            if (!chrCtx)
                return AVERROR(ENOMEM);
            desc[1].process = chr_planar_vscale;
            desc[1].instance = chrCtx;
            desc[1].src = src;
            desc[1].dst = dst;
        }
    } else {
        lumCtx = av_mallocz_array(sizeof(VScalerContext), 2);
        if (!lumCtx)
            return AVERROR(ENOMEM);
        chrCtx = &lumCtx[1];

        desc[0].process = c->yuv2packedX ? packed_vscale : any_vscale;
        desc[0].instance = lumCtx;
        desc[0].src = src;
        desc[0].dst = dst;
        desc[0].alpha = c->needAlpha;
    }

    ff_init_vscale_pfn(c, c->yuv2plane1, c->yuv2planeX, c->yuv2nv12cX,
        c->yuv2packed1, c->yuv2packed2, c->yuv2packedX, c->yuv2anyX, c->use_mmx_vfilter);
    return 0;
}