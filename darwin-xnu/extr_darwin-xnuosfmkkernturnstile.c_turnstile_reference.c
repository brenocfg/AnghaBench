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
struct turnstile {int /*<<< orphan*/  ts_refcount; } ;

/* Variables and functions */
 struct turnstile* TURNSTILE_NULL ; 
 int /*<<< orphan*/  os_ref_retain (int /*<<< orphan*/ *) ; 

void
turnstile_reference(struct turnstile *turnstile)
{
	if (turnstile == TURNSTILE_NULL) {
		return;
	}
	os_ref_retain(&turnstile->ts_refcount);
}