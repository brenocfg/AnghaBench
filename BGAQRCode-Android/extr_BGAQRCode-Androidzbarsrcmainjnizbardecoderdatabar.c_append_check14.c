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

/* Variables and functions */

__attribute__((used)) static inline void
append_check14 (unsigned char *buf)
{
    unsigned char chk = 0, d;
    int i;
    for(i = 13; --i >= 0; ) {
        d = *(buf++) - '0';
        chk += d;
        if(!(i & 1))
            chk += d << 1;
    }
    chk %= 10;
    if(chk)
        chk = 10 - chk;
    *buf = chk + '0';
}