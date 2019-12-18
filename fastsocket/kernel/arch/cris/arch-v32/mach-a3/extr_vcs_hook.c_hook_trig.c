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

/* Variables and functions */
 int /*<<< orphan*/  HOOK_TRIG (unsigned int) ; 
 unsigned int VHOOK_DATA (int) ; 
 unsigned int* hook_base ; 

__attribute__((used)) static unsigned hook_trig(unsigned id)
{
	unsigned ret;

	/* preempt_disable(); */

	/* Dummy read from mem to make sure data has propagated to memory
	 * before trigging */
	ret = *hook_base;

	/* trigger hook */
	HOOK_TRIG(id);

	/* wait for call to finish */
	while (VHOOK_DATA(0) > 0) ;

	/* extract return value */

	ret = VHOOK_DATA(1);

	return ret;
}