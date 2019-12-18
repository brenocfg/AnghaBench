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
typedef  scalar_t__ user_addr_t ;
typedef  scalar_t__ uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ RETURN_OFFSET ; 
 scalar_t__ dtrace_fuword32 (scalar_t__) ; 

__attribute__((used)) static int
dtrace_getustack_common(uint64_t * pcstack, int pcstack_limit, user_addr_t pc,
			user_addr_t sp)
{
	int ret = 0;
	
	ASSERT(pcstack == NULL || pcstack_limit > 0);

	while (pc != 0) {
		ret++;
		if (pcstack != NULL) {
			*pcstack++ = (uint64_t) pc;
			pcstack_limit--;
			if (pcstack_limit <= 0)
				break;
		}

		if (sp == 0)
			break;

		pc = dtrace_fuword32((sp + RETURN_OFFSET));
		sp = dtrace_fuword32(sp);
	}

	return (ret);
}