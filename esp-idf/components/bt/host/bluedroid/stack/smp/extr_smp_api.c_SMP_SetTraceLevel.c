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
typedef  int UINT8 ;
struct TYPE_2__ {int trace_level; } ;

/* Variables and functions */
 TYPE_1__ smp_cb ; 

extern UINT8 SMP_SetTraceLevel (UINT8 new_level)
{
    if (new_level != 0xFF) {
        smp_cb.trace_level = new_level;
    }

    return (smp_cb.trace_level);
}