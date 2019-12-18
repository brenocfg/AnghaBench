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
typedef  size_t xstate_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ ** ifps_zone ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ *,void*) ; 

__attribute__((used)) static inline void
fp_state_free(void *ifps, xstate_t xs)
{
	assert(ifps_zone[xs] != NULL);
	zfree(ifps_zone[xs], ifps);
}