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
 int UINT_MAX ; 

__attribute__((used)) static uint32_t get_v(uint8_t *p)
{
    uint32_t v = 0;

    do {
        if (v >= UINT_MAX / 128 - *p)
            return v;
        v <<= 7;
        v += *p & 0x7f;
    } while (*p++ & 0x80);

    return v;
}