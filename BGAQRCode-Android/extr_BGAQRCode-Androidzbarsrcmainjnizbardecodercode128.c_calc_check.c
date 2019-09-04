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

__attribute__((used)) static inline unsigned char calc_check (unsigned char c)
{
    if(!(c & 0x80))
        return(0x18);
    c &= 0x7f;
    if(c < 0x3d)
        return((c < 0x30 && c != 0x17) ? 0x10 : 0x20);
    if(c < 0x50)
        return((c == 0x4d) ? 0x20 : 0x10);
    return((c < 0x67) ? 0x20 : 0x10);
}