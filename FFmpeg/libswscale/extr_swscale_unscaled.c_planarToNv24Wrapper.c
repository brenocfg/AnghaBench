#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_3__ {scalar_t__ dstFormat; int /*<<< orphan*/  chrSrcW; int /*<<< orphan*/  srcW; } ;
typedef  TYPE_1__ SwsContext ;

/* Variables and functions */
 scalar_t__ AV_PIX_FMT_NV24 ; 
 int /*<<< orphan*/  copyPlane (int /*<<< orphan*/  const*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  interleaveBytes (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int planarToNv24Wrapper(SwsContext *c, const uint8_t *src[],
                               int srcStride[], int srcSliceY,
                               int srcSliceH, uint8_t *dstParam[],
                               int dstStride[])
{
    uint8_t *dst = dstParam[1] + dstStride[1] * srcSliceY;

    copyPlane(src[0], srcStride[0], srcSliceY, srcSliceH, c->srcW,
              dstParam[0], dstStride[0]);

    if (c->dstFormat == AV_PIX_FMT_NV24)
        interleaveBytes(src[1], src[2], dst, c->chrSrcW, srcSliceH,
                        srcStride[1], srcStride[2], dstStride[1]);
    else
        interleaveBytes(src[2], src[1], dst, c->chrSrcW, srcSliceH,
                        srcStride[2], srcStride[1], dstStride[1]);

    return srcSliceH;
}