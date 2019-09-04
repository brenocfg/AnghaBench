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
struct TYPE_3__ {scalar_t__ srcW; } ;
typedef  TYPE_1__ SwsContext ;

/* Variables and functions */
 scalar_t__ FFABS (int) ; 
 int /*<<< orphan*/  av_assert1 (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int packedCopyWrapper(SwsContext *c, const uint8_t *src[],
                             int srcStride[], int srcSliceY, int srcSliceH,
                             uint8_t *dst[], int dstStride[])
{
    if (dstStride[0] == srcStride[0] && srcStride[0] > 0)
        memcpy(dst[0] + dstStride[0] * srcSliceY, src[0], srcSliceH * dstStride[0]);
    else {
        int i;
        const uint8_t *srcPtr = src[0];
        uint8_t *dstPtr = dst[0] + dstStride[0] * srcSliceY;
        int length = 0;

        /* universal length finder */
        while (length + c->srcW <= FFABS(dstStride[0]) &&
               length + c->srcW <= FFABS(srcStride[0]))
            length += c->srcW;
        av_assert1(length != 0);

        for (i = 0; i < srcSliceH; i++) {
            memcpy(dstPtr, srcPtr, length);
            srcPtr += srcStride[0];
            dstPtr += dstStride[0];
        }
    }
    return srcSliceH;
}