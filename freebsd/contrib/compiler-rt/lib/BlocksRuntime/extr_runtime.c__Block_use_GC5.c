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
 int /*<<< orphan*/  _Block_memmove_gc_broken ; 
 int /*<<< orphan*/  _Block_use_GC (void* (*) (unsigned long const,int const,int const),void (*) (void const*,int const),void (*) (void*,void**),void (*) (void const*,void*),int /*<<< orphan*/ ) ; 

void _Block_use_GC5( void *(*alloc)(const unsigned long, const bool isOne, const bool isObject),
                    void (*setHasRefcount)(const void *, const bool),
                    void (*gc_assign)(void *, void **),
                    void (*gc_assign_weak)(const void *, void *)) {
    /* until objc calls _Block_use_GC it will call us; supply a broken internal memmove implementation until then */
    _Block_use_GC(alloc, setHasRefcount, gc_assign, gc_assign_weak, _Block_memmove_gc_broken);
}