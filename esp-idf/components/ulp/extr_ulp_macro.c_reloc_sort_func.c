#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ label; scalar_t__ type; } ;
typedef  TYPE_1__ reloc_info_t ;

/* Variables and functions */

__attribute__((used)) static int reloc_sort_func(const void* p_lhs, const void* p_rhs)
{
    const reloc_info_t lhs = *(const reloc_info_t*) p_lhs;
    const reloc_info_t rhs = *(const reloc_info_t*) p_rhs;
    if (lhs.label < rhs.label) {
        return -1;
    } else if (lhs.label > rhs.label) {
        return 1;
    }
    // label numbers are equal
    if (lhs.type < rhs.type) {
        return -1;
    } else if (lhs.type > rhs.type) {
        return 1;
    }

    // both label number and type are equal
    return 0;
}