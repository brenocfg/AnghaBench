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

/* Variables and functions */
 int /*<<< orphan*/  atomicGet (size_t,size_t,int /*<<< orphan*/ *) ; 
 size_t used_memory ; 
 int /*<<< orphan*/  used_memory_mutex ; 
 scalar_t__ zmalloc_thread_safe ; 

size_t zmalloc_used_memory(void) {
    size_t um;

    if (zmalloc_thread_safe) {
        atomicGet(used_memory,um,&used_memory_mutex);
    } else {
        um = used_memory;
    }
    return um;
}