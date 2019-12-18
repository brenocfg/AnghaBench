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
 int /*<<< orphan*/  AR9170_MAC_REG_BCN_PERIOD ; 
 int /*<<< orphan*/  AR9170_MAC_REG_PRETBTT ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 scalar_t__ IS_ERR_OR_NULL (struct carlu*) ; 
 int PTR_ERR (struct carlu*) ; 
 int /*<<< orphan*/  carlu_cmd_write_mem (struct carlu*,int /*<<< orphan*/ ,int) ; 
 int carlu_init () ; 
 int /*<<< orphan*/  carlu_loopback_test (struct carlu*,int,int,int,int) ; 
 int /*<<< orphan*/  carlusb_close (struct carlu*) ; 
 struct carlu* carlusb_probe () ; 

__attribute__((used)) static int carlu_run_loop_test(void)
{
	struct carlu *carl;
	int err;

	err = carlu_init();
	if (err)
		return EXIT_FAILURE;

	carl = carlusb_probe();
	if (IS_ERR_OR_NULL(carl)) {
		err = PTR_ERR(carl);
		goto out;
	}

	carlu_cmd_write_mem(carl, AR9170_MAC_REG_BCN_PERIOD, 0xFFFFFFFF);
	carlu_cmd_write_mem(carl, AR9170_MAC_REG_PRETBTT, 0xFFFFFFFF);

	/* different payload test */
	carlu_loopback_test(carl, 9000, 1000, 1566, 1566);
	carlusb_close(carl);

out:
	return err ? EXIT_FAILURE : EXIT_SUCCESS;
}