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
struct TYPE_3__ {int /*<<< orphan*/  srcW; } ;
typedef  TYPE_1__ SwsContext ;

/* Variables and functions */
 int /*<<< orphan*/  yv12touyvy (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 

__attribute__((used)) static int planarToUyvyWrapper(SwsContext *c, const uint8_t *src[],
                               int srcStride[], int srcSliceY, int srcSliceH,
                               uint8_t *dstParam[], int dstStride[])
{
    uint8_t *dst = dstParam[0] + dstStride[0] * srcSliceY;

    yv12touyvy(src[0], src[1], src[2], dst, c->srcW, srcSliceH, srcStride[0],
               srcStride[1], dstStride[0]);

    return srcSliceH;
}