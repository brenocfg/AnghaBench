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
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  turnstile_init (struct turnstile*) ; 
 int /*<<< orphan*/  turnstiles_zone ; 
 struct turnstile* zalloc (int /*<<< orphan*/ ) ; 

struct turnstile *
turnstile_alloc(void)
{
	struct turnstile *turnstile = TURNSTILE_NULL;

	turnstile = zalloc(turnstiles_zone);
	turnstile_init(turnstile);

#if DEVELOPMENT || DEBUG
	/* Add turnstile to global list */
	global_turnstiles_lock();
	queue_enter(&turnstiles_list, turnstile,
		struct turnstile *, ts_global_elm);
	global_turnstiles_unlock();
#endif
	return turnstile;
}