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
typedef  int uint32_t ;

/* Variables and functions */
 int ABSDIFF (int,int) ; 
 int UMASK ; 
 int VMASK ; 
 int YMASK ; 

__attribute__((used)) static uint32_t pixel_diff(uint32_t x, uint32_t y, const uint32_t *r2y)
{
#define YMASK 0xff0000
#define UMASK 0x00ff00
#define VMASK 0x0000ff
#define ABSDIFF(a,b) (abs((int)(a)-(int)(b)))

    uint32_t yuv1 = r2y[x & 0xffffff];
    uint32_t yuv2 = r2y[y & 0xffffff];

    return (ABSDIFF(yuv1 & YMASK, yuv2 & YMASK) >> 16) +
           (ABSDIFF(yuv1 & UMASK, yuv2 & UMASK) >>  8) +
            ABSDIFF(yuv1 & VMASK, yuv2 & VMASK);
}