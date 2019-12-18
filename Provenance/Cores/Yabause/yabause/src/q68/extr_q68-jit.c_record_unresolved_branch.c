#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct TYPE_3__ {scalar_t__ m68k_target; scalar_t__ native_offset; } ;

/* Variables and functions */
 int lenof (TYPE_1__*) ; 
 TYPE_1__* unres_branches ; 

__attribute__((used)) static void record_unresolved_branch(uint32_t m68k_target,
                                     uint32_t native_offset)
{
    int oldest = 0;
    int i;
    for (i = 0; i < lenof(unres_branches); i++) {
        if (unres_branches[i].m68k_target == 0) {
            oldest = i;
            break;
        } else if (unres_branches[i].native_offset
                   < unres_branches[oldest].native_offset) {
            oldest = i;
        }
    }
    unres_branches[oldest].m68k_target   = m68k_target;
    unres_branches[oldest].native_offset = native_offset;
}