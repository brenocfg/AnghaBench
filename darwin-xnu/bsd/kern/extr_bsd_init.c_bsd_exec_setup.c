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
 int BSD_PAGEABLE_SIZE_PER_EXEC ; 
 int BSD_SIMUL_EXECS ; 
 int bsd_pageable_map_size ; 
 int bsd_simul_execs ; 

void
bsd_exec_setup(int scale)
{

	switch (scale) {
		case 0:
		case 1:
			bsd_simul_execs = BSD_SIMUL_EXECS;
			break;
		case 2:
		case 3:
			bsd_simul_execs = 65;
			break;
		case 4:
		case 5:
			bsd_simul_execs = 129;
			break;
		case 6:
		case 7:
			bsd_simul_execs = 257;
			break;
		default:
			bsd_simul_execs = 513;
			break;
			
	}
	bsd_pageable_map_size = (bsd_simul_execs * BSD_PAGEABLE_SIZE_PER_EXEC);
}