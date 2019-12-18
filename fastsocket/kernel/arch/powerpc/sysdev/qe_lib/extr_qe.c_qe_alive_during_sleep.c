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
 int /*<<< orphan*/  of_find_compatible_node (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

int qe_alive_during_sleep(void)
{
	static int ret = -1;

	if (ret != -1)
		return ret;

	ret = !of_find_compatible_node(NULL, NULL, "fsl,mpc8569-pmc");

	return ret;
}