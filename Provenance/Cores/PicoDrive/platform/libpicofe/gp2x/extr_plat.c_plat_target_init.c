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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  GP2X_DEV_CAANOO ; 
 int /*<<< orphan*/  GP2X_DEV_GP2X ; 
 int /*<<< orphan*/  GP2X_DEV_WIZ ; 
#define  SOCID_MMSP2 129 
#define  SOCID_POLLUX 128 
 int default_cpu_clock ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  gp2x_dev_id ; 
 int /*<<< orphan*/  mmsp2_init () ; 
 int /*<<< orphan*/  pollux_init () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int soc_detect () ; 

int plat_target_init(void)
{
	gp2x_soc_t soc;
	FILE *f;

	soc = soc_detect();
	switch (soc)
	{
	case SOCID_MMSP2:
		mmsp2_init();
		default_cpu_clock = 200;
		gp2x_dev_id = GP2X_DEV_GP2X;
		break;
	case SOCID_POLLUX:
		pollux_init();
		default_cpu_clock = 533;
		f = fopen("/dev/accel", "rb");
		if (f) {
			printf("detected Caanoo\n");
			gp2x_dev_id = GP2X_DEV_CAANOO;
			fclose(f);
		}
		else {
			printf("detected Wiz\n");
			gp2x_dev_id = GP2X_DEV_WIZ;
		}
		break;
	default:
		printf("could not recognize SoC.\n");
		break;
	}

	return 0;
}