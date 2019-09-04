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
typedef  int /*<<< orphan*/  tcache_t ;
typedef  int /*<<< orphan*/  arena_t ;

/* Variables and functions */
 int /*<<< orphan*/  tcache_arena_associate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tcache_arena_dissociate (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
tcache_arena_reassociate(tcache_t *tcache, arena_t *oldarena, arena_t *newarena)
{

	tcache_arena_dissociate(tcache, oldarena);
	tcache_arena_associate(tcache, newarena);
}