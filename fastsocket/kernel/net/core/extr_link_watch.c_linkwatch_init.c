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
 scalar_t__ create_singlethread_workqueue (char*) ; 
 scalar_t__ linkwatch_wq ; 

int linkwatch_init(void)
{
	linkwatch_wq = create_singlethread_workqueue("linkwatch");
	return linkwatch_wq ? 0 : -ENOMEM;
}