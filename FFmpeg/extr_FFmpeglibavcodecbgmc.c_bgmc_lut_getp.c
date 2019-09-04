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
 scalar_t__ LUT_BUFF ; 
 unsigned int LUT_SIZE ; 
 unsigned int av_clip (int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bgmc_lut_fillp (int /*<<< orphan*/ *,int*,int) ; 

__attribute__((used)) static uint8_t *bgmc_lut_getp(uint8_t *lut, int *lut_status, int delta)
{
    unsigned int i = av_clip(delta, 0, LUT_BUFF - 1);

    lut += (i * LUT_SIZE) << 4;

    if (lut_status[i] != delta)
        bgmc_lut_fillp(lut, &lut_status[i], delta);

    return lut;
}