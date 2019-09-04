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
struct turnstile {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  TURNSTILE_INTERLOCK_NOT_HELD ; 
 int /*<<< orphan*/  assert (struct turnstile*) ; 
 int /*<<< orphan*/  turnstile_update_inheritor_complete (struct turnstile*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
psynch_wait_update_complete(struct turnstile *ts)
{
	assert(ts);
	turnstile_update_inheritor_complete(ts, TURNSTILE_INTERLOCK_NOT_HELD);
}