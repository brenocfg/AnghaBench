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
typedef  int uint16_t ;

/* Variables and functions */

__attribute__((used)) static void unpack_3(const uint8_t b[3], uint16_t s[16])
{
    int i;

    s[0] = (b[0] << 8) | b[1];

    if (s[0] & 0x8000)
        s[0] &= 0x7fff;
    else
        s[0] = ~s[0];

    for (i = 1; i < 16; i++)
        s[i] = s[0];
}