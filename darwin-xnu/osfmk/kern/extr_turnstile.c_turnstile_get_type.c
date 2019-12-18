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
union turnstile_type_gencount {int /*<<< orphan*/  ts_type; int /*<<< orphan*/  value; } ;
typedef  int /*<<< orphan*/  turnstile_type_t ;
struct turnstile {int /*<<< orphan*/  ts_type_gencount; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomic_load_explicit (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memory_order_relaxed ; 

__attribute__((used)) static turnstile_type_t
turnstile_get_type(struct turnstile *turnstile)
{
	union turnstile_type_gencount type_and_gencount;

	type_and_gencount.value = atomic_load_explicit(&turnstile->ts_type_gencount, memory_order_relaxed);
	return (turnstile_type_t) type_and_gencount.ts_type;
}