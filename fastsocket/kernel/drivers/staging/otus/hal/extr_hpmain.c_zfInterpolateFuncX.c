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
typedef  scalar_t__ u8_t ;
typedef  int s32_t ;

/* Variables and functions */
 int ZM_MULTIPLIER ; 
 int zfInterpolateFunc (int,int,int,int,int) ; 

u8_t zfInterpolateFuncX(u8_t x, u8_t x1, u8_t y1, u8_t x2, u8_t y2)
{
    s32_t y;
    s32_t inc;

    #define ZM_MULTIPLIER   8
    y = zfInterpolateFunc((s32_t)x<<ZM_MULTIPLIER,
                          (s32_t)x1<<ZM_MULTIPLIER,
                          (s32_t)y1<<ZM_MULTIPLIER,
                          (s32_t)x2<<ZM_MULTIPLIER,
                          (s32_t)y2<<ZM_MULTIPLIER);

    inc = (y & (1<<(ZM_MULTIPLIER-1))) >> (ZM_MULTIPLIER-1);
    y = (y >> ZM_MULTIPLIER) + inc;
    #undef ZM_MULTIPLIER

    return (u8_t)y;
}