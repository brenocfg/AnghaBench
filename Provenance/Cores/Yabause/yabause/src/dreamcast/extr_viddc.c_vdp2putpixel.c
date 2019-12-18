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
typedef  scalar_t__ uint8 ;
typedef  int /*<<< orphan*/  u16 ;
typedef  int s32 ;

/* Variables and functions */
 int /*<<< orphan*/ * vdp2_fb ; 
 scalar_t__** vdp2_prio ; 

__attribute__((used)) static inline void vdp2putpixel(s32 x, s32 y, u16 color, int priority)  {
    vdp2_fb[(y * 512) + x] = color;
    vdp2_prio[x][y] = (uint8) priority;
}