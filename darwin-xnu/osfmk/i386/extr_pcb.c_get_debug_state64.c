#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  x86_debug_state64_t ;
typedef  TYPE_2__* thread_t ;
struct TYPE_4__ {scalar_t__ ids; } ;
struct TYPE_5__ {TYPE_1__ machine; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  copy_debug_state64 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
get_debug_state64(thread_t thread, x86_debug_state64_t *ds)
{
	x86_debug_state64_t *saved_state;

	saved_state = (x86_debug_state64_t *)thread->machine.ids;

	if (saved_state) {
		copy_debug_state64(saved_state, ds, TRUE);
	} else
		bzero(ds, sizeof *ds);
}