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
typedef  int gp2x_soc_t ;

/* Variables and functions */
#define  SOCID_MMSP2 129 
#define  SOCID_POLLUX 128 
 int /*<<< orphan*/  mmsp2_finish () ; 
 int /*<<< orphan*/  pollux_finish () ; 
 int soc_detect () ; 

void plat_target_finish(void)
{
	gp2x_soc_t soc;

	soc = soc_detect();
	switch (soc)
	{
	case SOCID_MMSP2:
		mmsp2_finish();
		break;
	case SOCID_POLLUX:
		pollux_finish();
		break;
	default:
		break;
	}
}