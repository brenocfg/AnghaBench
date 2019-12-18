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

__attribute__((used)) static int64_t find_header(const char *p)
{
    int64_t offset = 0;
    while(p[offset] == ' ' || p[offset] == '\t') {
        offset++;
    }
    if(p[offset] == '[' && p[offset + 1] >= 'a' && p[offset + 1] <= 'z') {
        return offset;
    } else {
        return -1;
    }
}