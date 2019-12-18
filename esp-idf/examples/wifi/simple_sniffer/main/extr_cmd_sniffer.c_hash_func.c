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
typedef  char uint32_t ;

/* Variables and functions */

__attribute__((used)) static uint32_t hash_func(const char *str, uint32_t max_num)
{
    uint32_t ret = 0;
    char *p = (char *)str;
    while (*p) {
        ret += *p;
        p++;
    }
    return ret % max_num;
}