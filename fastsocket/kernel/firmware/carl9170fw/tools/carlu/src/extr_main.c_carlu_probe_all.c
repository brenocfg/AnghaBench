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
struct carlu {int dummy; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (struct carlu**) ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ IS_ERR_OR_NULL (struct carlu*) ; 
 int /*<<< orphan*/  carlu_exit () ; 
 int carlu_init () ; 
 int /*<<< orphan*/  carlusb_close (struct carlu*) ; 
 struct carlu* carlusb_probe () ; 
 int /*<<< orphan*/  info (char*,unsigned int) ; 

__attribute__((used)) static int carlu_probe_all(void)
{
	struct carlu *carl[32] = { 0 };
	unsigned int devs;
	int ret;

	ret = carlu_init();
	if (ret)
		return EXIT_FAILURE;

	for (devs = 0; devs < ARRAY_SIZE(carl); devs++) {
		carl[devs] = carlusb_probe();
		if (IS_ERR_OR_NULL(carl[devs]))
			break;
	}

	info("Found %d devices\n", devs);

	for (; devs > 0; devs--)
		carlusb_close(carl[devs - 1]);

	carlu_exit();
	return EXIT_SUCCESS;
}