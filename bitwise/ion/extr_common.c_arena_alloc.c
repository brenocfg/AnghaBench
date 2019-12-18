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
struct TYPE_4__ {void* end; void* ptr; } ;
typedef  TYPE_1__ Arena ;

/* Variables and functions */
 void* ALIGN_DOWN_PTR (void*,int /*<<< orphan*/ ) ; 
 void* ALIGN_UP_PTR (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARENA_ALIGNMENT ; 
 int /*<<< orphan*/  arena_grow (TYPE_1__*,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 

void *arena_alloc(Arena *arena, size_t size) {
    if (size > (size_t)(arena->end - arena->ptr)) {
        arena_grow(arena, size);
        assert(size <= (size_t)(arena->end - arena->ptr));
    }
    void *ptr = arena->ptr;
    arena->ptr = ALIGN_UP_PTR(arena->ptr + size, ARENA_ALIGNMENT);
    assert(arena->ptr <= arena->end);
    assert(ptr == ALIGN_DOWN_PTR(ptr, ARENA_ALIGNMENT));
    return ptr;
}