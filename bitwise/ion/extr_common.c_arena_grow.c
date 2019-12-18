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
struct TYPE_3__ {int /*<<< orphan*/  ptr; int /*<<< orphan*/  blocks; scalar_t__ end; } ;
typedef  TYPE_1__ Arena ;

/* Variables and functions */
 int /*<<< orphan*/  ALIGN_DOWN_PTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ALIGN_UP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ARENA_ALIGNMENT ; 
 int /*<<< orphan*/  ARENA_BLOCK_SIZE ; 
 int /*<<< orphan*/  CLAMP_MIN (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  buf_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmalloc (size_t) ; 

void arena_grow(Arena *arena, size_t min_size) {
    size_t size = ALIGN_UP(CLAMP_MIN(min_size, ARENA_BLOCK_SIZE), ARENA_ALIGNMENT);
    arena->ptr = xmalloc(size);
    assert(arena->ptr == ALIGN_DOWN_PTR(arena->ptr, ARENA_ALIGNMENT));
    arena->end = arena->ptr + size;
    buf_push(arena->blocks, arena->ptr);
}