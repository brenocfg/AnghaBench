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
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/ * iucv_path_table ; 
 int /*<<< orphan*/  iucv_retrieve_cpu ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  put_online_cpus () ; 

__attribute__((used)) static void iucv_disable(void)
{
	get_online_cpus();
	on_each_cpu(iucv_retrieve_cpu, NULL, 1);
	kfree(iucv_path_table);
	iucv_path_table = NULL;
	put_online_cpus();
}