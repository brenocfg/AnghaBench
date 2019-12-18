#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ m_map; scalar_t__ m_entry; } ;
typedef  TYPE_1__ atf_map_iter_t ;

/* Variables and functions */

bool
atf_equal_map_iter_map_iter(const atf_map_iter_t i1,
                            const atf_map_iter_t i2)
{
    return i1.m_map == i2.m_map && i1.m_entry == i2.m_entry;
}