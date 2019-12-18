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
typedef  int /*<<< orphan*/  chunk_hooks_t ;
struct TYPE_3__ {int /*<<< orphan*/  chunk_hooks; } ;
typedef  TYPE_1__ arena_t ;

/* Variables and functions */

__attribute__((used)) static chunk_hooks_t
chunk_hooks_get_locked(arena_t *arena)
{

	return (arena->chunk_hooks);
}