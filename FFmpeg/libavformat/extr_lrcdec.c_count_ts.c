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
typedef  size_t int64_t ;

/* Variables and functions */

__attribute__((used)) static int64_t count_ts(const char *p)
{
    int64_t offset = 0;
    int in_brackets = 0;

    for(;;) {
        if(p[offset] == ' ' || p[offset] == '\t') {
            offset++;
        } else if(p[offset] == '[') {
            offset++;
            in_brackets++;
        } else if (p[offset] == ']' && in_brackets) {
            offset++;
            in_brackets--;
        } else if(in_brackets &&
                 (p[offset] == ':' || p[offset] == '.' || p[offset] == '-' ||
                 (p[offset] >= '0' && p[offset] <= '9'))) {
            offset++;
        } else {
            break;
        }
    }
    return offset;
}