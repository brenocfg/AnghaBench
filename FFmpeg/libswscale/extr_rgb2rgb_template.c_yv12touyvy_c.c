#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 int /*<<< orphan*/  yuvPlanartouyvy_c (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/ *,int,int,int,int,int,int) ; 

__attribute__((used)) static inline void yv12touyvy_c(const uint8_t *ysrc, const uint8_t *usrc,
                                const uint8_t *vsrc, uint8_t *dst,
                                int width, int height, int lumStride,
                                int chromStride, int dstStride)
{
    //FIXME interpolate chroma
    yuvPlanartouyvy_c(ysrc, usrc, vsrc, dst, width, height, lumStride,
                      chromStride, dstStride, 2);
}