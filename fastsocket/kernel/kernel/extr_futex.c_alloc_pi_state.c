#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct futex_pi_state {int dummy; } ;
struct TYPE_2__ {struct futex_pi_state* pi_state_cache; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 TYPE_1__* current ; 

__attribute__((used)) static struct futex_pi_state * alloc_pi_state(void)
{
	struct futex_pi_state *pi_state = current->pi_state_cache;

	WARN_ON(!pi_state);
	current->pi_state_cache = NULL;

	return pi_state;
}