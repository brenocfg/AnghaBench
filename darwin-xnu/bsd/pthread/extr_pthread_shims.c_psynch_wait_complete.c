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
 int /*<<< orphan*/  assert (struct turnstile**) ; 
 int /*<<< orphan*/  turnstile_complete (uintptr_t,struct turnstile**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
psynch_wait_complete(uintptr_t kwq, struct turnstile **tstore)
{
	assert(tstore);
	turnstile_complete(kwq, tstore, NULL);
}