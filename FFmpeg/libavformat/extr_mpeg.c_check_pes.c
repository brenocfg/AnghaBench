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

/* Variables and functions */

__attribute__((used)) static int check_pes(const uint8_t *p, const uint8_t *end)
{
    int pes1;
    int pes2 = (p[3] & 0xC0) == 0x80 &&
               (p[4] & 0xC0) != 0x40 &&
               ((p[4] & 0xC0) == 0x00 ||
                (p[4] & 0xC0) >> 2 == (p[6] & 0xF0));

    for (p += 3; p < end && *p == 0xFF; p++) ;
    if ((*p & 0xC0) == 0x40)
        p += 2;

    if ((*p & 0xF0) == 0x20)
        pes1 = p[0] & p[2] & p[4] & 1;
    else if ((*p & 0xF0) == 0x30)
        pes1 = p[0] & p[2] & p[4] & p[5] & p[7] & p[9] & 1;
    else
        pes1 = *p == 0x0F;

    return pes1 || pes2;
}