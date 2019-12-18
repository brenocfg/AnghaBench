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
 int /*<<< orphan*/  cleanup_srcu_struct (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  srcu_ctl ; 
 int /*<<< orphan*/  synchronize_srcu (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void srcu_torture_cleanup(void)
{
	synchronize_srcu(&srcu_ctl);
	cleanup_srcu_struct(&srcu_ctl);
}