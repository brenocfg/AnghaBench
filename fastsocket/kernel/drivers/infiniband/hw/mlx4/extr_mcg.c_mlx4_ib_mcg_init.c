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
 int ENOMEM ; 
 int /*<<< orphan*/  clean_wq ; 
 int /*<<< orphan*/  create_singlethread_workqueue (char*) ; 

int mlx4_ib_mcg_init(void)
{
	clean_wq = create_singlethread_workqueue("mlx4_ib_mcg");
	if (!clean_wq)
		return -ENOMEM;

	return 0;
}