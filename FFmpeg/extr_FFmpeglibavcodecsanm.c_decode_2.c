#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int aligned_height; int aligned_width; } ;
typedef  TYPE_1__ SANMVideoContext ;

/* Variables and functions */
 int codec2subblock (TYPE_1__*,int,int,int) ; 

__attribute__((used)) static int decode_2(SANMVideoContext *ctx)
{
    int cx, cy, ret;

    for (cy = 0; cy < ctx->aligned_height; cy += 8)
        for (cx = 0; cx < ctx->aligned_width; cx += 8)
            if (ret = codec2subblock(ctx, cx, cy, 8))
                return ret;

    return 0;
}