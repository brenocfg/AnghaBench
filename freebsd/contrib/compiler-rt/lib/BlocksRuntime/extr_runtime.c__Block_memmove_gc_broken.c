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
 int /*<<< orphan*/  _Block_assign_default (void*,void**) ; 

__attribute__((used)) static void _Block_memmove_gc_broken(void *dest, void *src, unsigned long size) {
    void **destp = (void **)dest;
    void **srcp = (void **)src;
    while (size) {
        _Block_assign_default(*srcp, destp);
        destp++;
        srcp++;
        size -= sizeof(void *);
    }
}