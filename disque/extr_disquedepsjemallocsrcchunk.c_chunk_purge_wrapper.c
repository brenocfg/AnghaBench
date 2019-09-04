#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int (* purge ) (void*,size_t,size_t,size_t,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ chunk_hooks_t ;
struct TYPE_8__ {int /*<<< orphan*/  ind; } ;
typedef  TYPE_2__ arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  chunk_hooks_assure_initialized (TYPE_2__*,TYPE_1__*) ; 
 int stub1 (void*,size_t,size_t,size_t,int /*<<< orphan*/ ) ; 

bool
chunk_purge_wrapper(arena_t *arena, chunk_hooks_t *chunk_hooks, void *chunk,
    size_t size, size_t offset, size_t length)
{

	chunk_hooks_assure_initialized(arena, chunk_hooks);
	return (chunk_hooks->purge(chunk, size, offset, length, arena->ind));
}