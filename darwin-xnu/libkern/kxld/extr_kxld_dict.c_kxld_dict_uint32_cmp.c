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
typedef  scalar_t__ uint32_t ;
typedef  int u_int ;

/* Variables and functions */

u_int
kxld_dict_uint32_cmp(const void *key1, const void *key2)
{
    const uint32_t *a = key1;
    const uint32_t *b = key2;

    return (a && b && (*a == *b));
}