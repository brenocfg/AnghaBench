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
typedef  char uint8_t ;

/* Variables and functions */
 char* av_malloc (int) ; 

__attribute__((used)) static uint8_t *unescape(const uint8_t *buf, int size)
{
    uint8_t *ret = av_malloc(size + 1);
    uint8_t *p1  = ret;
    const uint8_t *p2 = buf;

    if (!ret)
        return NULL;

    while (p2 < buf + size) {
        if (*p2 == '\\')
            p2++;
        *p1++ = *p2++;
    }
    *p1 = 0;
    return ret;
}