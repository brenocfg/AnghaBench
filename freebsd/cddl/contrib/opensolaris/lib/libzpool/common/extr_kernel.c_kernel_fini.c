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
 int /*<<< orphan*/  close (int) ; 
 int random_fd ; 
 int /*<<< orphan*/  spa_fini () ; 
 int /*<<< orphan*/  system_taskq_fini () ; 
 int urandom_fd ; 

void
kernel_fini(void)
{
	spa_fini();

	system_taskq_fini();

	close(random_fd);
	close(urandom_fd);

	random_fd = -1;
	urandom_fd = -1;
}