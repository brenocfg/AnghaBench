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
 void* arena_alloc (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ast_arena ; 
 size_t ast_memory_usage ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,size_t) ; 

void *ast_alloc(size_t size) {
    assert(size != 0);
    void *ptr = arena_alloc(&ast_arena, size);
    memset(ptr, 0, size);
    ast_memory_usage += size;
    return ptr;
}