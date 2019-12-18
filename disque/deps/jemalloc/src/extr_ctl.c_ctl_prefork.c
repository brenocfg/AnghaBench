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
 int /*<<< orphan*/  ctl_mtx ; 
 int /*<<< orphan*/  malloc_mutex_prefork (int /*<<< orphan*/ *) ; 

void
ctl_prefork(void)
{

	malloc_mutex_prefork(&ctl_mtx);
}