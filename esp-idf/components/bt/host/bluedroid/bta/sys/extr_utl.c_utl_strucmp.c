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

int utl_strucmp(const char *p_s, const char *p_t)
{
    char c;

    while (*p_s && *p_t) {
        c = *p_t++;
        if (c >= 'a' && c <= 'z') {
            c -= 0x20;
        }
        if (*p_s++ != c) {
            return -1;
        }
    }
    /* if p_t hit null first, no match */
    if (*p_t == 0 && *p_s != 0) {
        return 1;
    }
    /* else p_s hit null first, count as match */
    else {
        return 0;
    }
}