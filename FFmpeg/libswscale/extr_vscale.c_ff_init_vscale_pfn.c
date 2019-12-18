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
typedef  void* yuv2planarX_fn ;
typedef  void* yuv2planar1_fn ;
typedef  scalar_t__ yuv2packedX_fn ;
typedef  void* yuv2packed2_fn ;
typedef  void* yuv2packed1_fn ;
typedef  void* yuv2interleavedX_fn ;
typedef  void* yuv2anyX_fn ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_6__ {int filter_size; int isMMX; void* pfn; scalar_t__ yuv2packedX; int /*<<< orphan*/  filter_pos; int /*<<< orphan*/ ** filter; } ;
typedef  TYPE_2__ VScalerContext ;
struct TYPE_7__ {int numDesc; int vChrFilterSize; int vLumFilterSize; scalar_t__ yuv2packed2; scalar_t__ yuv2packed1; int /*<<< orphan*/  vChrFilterPos; int /*<<< orphan*/ * vChrFilter; int /*<<< orphan*/  vLumFilterPos; int /*<<< orphan*/ * vLumFilter; TYPE_1__* desc; scalar_t__ alpMmxFilter; scalar_t__ lumMmxFilter; scalar_t__ chrMmxFilter; int /*<<< orphan*/  dstFormat; scalar_t__ is_internal_gamma; } ;
struct TYPE_5__ {TYPE_2__* instance; } ;
typedef  TYPE_3__ SwsContext ;

/* Variables and functions */
 int /*<<< orphan*/  isALPHA (int /*<<< orphan*/ ) ; 
 scalar_t__ isGray (int /*<<< orphan*/ ) ; 
 scalar_t__ isPlanarYUV (int /*<<< orphan*/ ) ; 

void ff_init_vscale_pfn(SwsContext *c,
    yuv2planar1_fn yuv2plane1,
    yuv2planarX_fn yuv2planeX,
    yuv2interleavedX_fn yuv2nv12cX,
    yuv2packed1_fn yuv2packed1,
    yuv2packed2_fn yuv2packed2,
    yuv2packedX_fn yuv2packedX,
    yuv2anyX_fn yuv2anyX, int use_mmx)
{
    VScalerContext *lumCtx = NULL;
    VScalerContext *chrCtx = NULL;
    int idx = c->numDesc - (c->is_internal_gamma ? 2 : 1); //FIXME avoid hardcoding indexes

    if (isPlanarYUV(c->dstFormat) || (isGray(c->dstFormat) && !isALPHA(c->dstFormat))) {
        if (!isGray(c->dstFormat)) {
            chrCtx = c->desc[idx].instance;

            chrCtx->filter[0] = use_mmx ? (int16_t*)c->chrMmxFilter : c->vChrFilter;
            chrCtx->filter_size = c->vChrFilterSize;
            chrCtx->filter_pos = c->vChrFilterPos;
            chrCtx->isMMX = use_mmx;

            --idx;
            if (yuv2nv12cX)               chrCtx->pfn = yuv2nv12cX;
            else if (c->vChrFilterSize == 1) chrCtx->pfn = yuv2plane1;
            else                             chrCtx->pfn = yuv2planeX;
        }

        lumCtx = c->desc[idx].instance;

        lumCtx->filter[0] = use_mmx ? (int16_t*)c->lumMmxFilter : c->vLumFilter;
        lumCtx->filter[1] = use_mmx ? (int16_t*)c->alpMmxFilter : c->vLumFilter;
        lumCtx->filter_size = c->vLumFilterSize;
        lumCtx->filter_pos = c->vLumFilterPos;
        lumCtx->isMMX = use_mmx;

        if (c->vLumFilterSize == 1) lumCtx->pfn = yuv2plane1;
        else                        lumCtx->pfn = yuv2planeX;

    } else {
        lumCtx = c->desc[idx].instance;
        chrCtx = &lumCtx[1];

        lumCtx->filter[0] = c->vLumFilter;
        lumCtx->filter_size = c->vLumFilterSize;
        lumCtx->filter_pos = c->vLumFilterPos;

        chrCtx->filter[0] = c->vChrFilter;
        chrCtx->filter_size = c->vChrFilterSize;
        chrCtx->filter_pos = c->vChrFilterPos;

        lumCtx->isMMX = use_mmx;
        chrCtx->isMMX = use_mmx;

        if (yuv2packedX) {
            if (c->yuv2packed1 && c->vLumFilterSize == 1 && c->vChrFilterSize <= 2)
                lumCtx->pfn = yuv2packed1;
            else if (c->yuv2packed2 && c->vLumFilterSize == 2 && c->vChrFilterSize == 2)
                lumCtx->pfn = yuv2packed2;
            lumCtx->yuv2packedX = yuv2packedX;
        } else
            lumCtx->pfn = yuv2anyX;
    }
}