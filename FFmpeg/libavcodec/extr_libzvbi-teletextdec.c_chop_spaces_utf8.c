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

__attribute__((used)) static int chop_spaces_utf8(const unsigned char* t, int len)
{
    t += len;
    while (len > 0) {
        if (*--t != ' ' || (len-1 > 0 && *(t-1) & 0x80))
            break;
        --len;
    }
    return len;
}