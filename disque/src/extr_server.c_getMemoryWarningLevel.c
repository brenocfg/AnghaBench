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
struct TYPE_2__ {int maxmemory; size_t resident_set_size; } ;

/* Variables and functions */
 TYPE_1__ server ; 
 size_t zmalloc_used_memory () ; 

int getMemoryWarningLevel(void) {
    size_t mem_used = zmalloc_used_memory();

    if (mem_used > server.maxmemory / 100 * 95 &&
        mem_used > server.resident_set_size) return 3;
    if (mem_used > server.maxmemory / 100 * 95) return 2;
    if (mem_used > server.maxmemory / 100 * 75) return 1;
    return 0;
}