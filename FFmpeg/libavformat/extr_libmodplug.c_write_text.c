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

__attribute__((used)) static void write_text(uint8_t *dst, const char *s, int linesize, int x, int y)
{
    int i;
    dst += y*linesize + x*3;
    for (i = 0; s[i]; i++, dst += 3) {
        dst[0] = 0x0;   // count - 1
        dst[1] = s[i];  // char
        dst[2] = 0x0f;  // background / foreground
    }
}