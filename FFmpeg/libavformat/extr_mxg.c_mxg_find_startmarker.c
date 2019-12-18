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

/* Variables and functions */
 int AV_RN32 (int*) ; 

__attribute__((used)) static uint8_t* mxg_find_startmarker(uint8_t *p, uint8_t *end)
{
    for (; p < end - 3; p += 4) {
        uint32_t x = AV_RN32(p);

        if (x & (~(x+0x01010101)) & 0x80808080) {
            if (p[0] == 0xff) {
                return p;
            } else if (p[1] == 0xff) {
                return p+1;
            } else if (p[2] == 0xff) {
                return p+2;
            } else if (p[3] == 0xff) {
                return p+3;
            }
        }
    }

    for (; p < end; ++p) {
        if (*p == 0xff) return p;
    }

    return end;
}