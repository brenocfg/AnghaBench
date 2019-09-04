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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static inline void convert_write_rgb (uint8_t *dstp,
                                      uint32_t p,
                                      int bpp)
{
    if(bpp == 3) {
        *dstp = p & 0xff;
        *(dstp + 1) = (p >> 8) & 0xff;
        *(dstp + 2) = (p >> 16) & 0xff;
    }
    else if(bpp == 4)
        *((uint32_t*)dstp) = p;
    else if(bpp == 2)
        *((uint16_t*)dstp) = p;
    else
        *dstp = p;
}