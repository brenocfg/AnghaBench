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
typedef  void x86_fx_thread_state ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fp_state_size ; 
 int /*<<< orphan*/ ** ifps_zone ; 
 void* zalloc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
fp_state_alloc(xstate_t xs)
{
	struct x86_fx_thread_state *ifps;

	assert(ifps_zone[xs] != NULL);
	ifps = zalloc(ifps_zone[xs]);

#if	DEBUG	
	if (!(ALIGNED(ifps,64))) {
		panic("fp_state_alloc: %p, %u, %p, %u",
			ifps, (unsigned) ifps_zone[xs]->elem_size,
			(void *) ifps_zone[xs]->free_elements,
			(unsigned) ifps_zone[xs]->alloc_size);
	}
#endif
	bzero(ifps, fp_state_size[xs]);

	return ifps;
}