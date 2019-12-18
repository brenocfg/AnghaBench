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
typedef  scalar_t__ const int16_t ;

/* Variables and functions */

__attribute__((used)) static inline int in_table_int16(const int16_t *table, int last_el, int16_t needle)
{
    int i;
    for (i = 0; i <= last_el; i++)
        if (table[i] == needle)
            return 1;
    return 0;
}