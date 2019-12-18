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
typedef  int u64 ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int* ppc_inst_cmpl ; 

__attribute__((used)) static int p4_get_alternatives(u64 event, unsigned int flags, u64 alt[])
{
	int i, j, na;

	alt[0] = event;
	na = 1;

	/* 2 possibilities for PM_GRP_DISP_REJECT */
	if (event == 0x8003 || event == 0x0224) {
		alt[1] = event ^ (0x8003 ^ 0x0224);
		return 2;
	}

	/* 2 possibilities for PM_ST_MISS_L1 */
	if (event == 0x0c13 || event == 0x0c23) {
		alt[1] = event ^ (0x0c13 ^ 0x0c23);
		return 2;
	}

	/* several possibilities for PM_INST_CMPL */
	for (i = 0; i < ARRAY_SIZE(ppc_inst_cmpl); ++i) {
		if (event == ppc_inst_cmpl[i]) {
			for (j = 0; j < ARRAY_SIZE(ppc_inst_cmpl); ++j)
				if (j != i)
					alt[na++] = ppc_inst_cmpl[j];
			break;
		}
	}

	return na;
}