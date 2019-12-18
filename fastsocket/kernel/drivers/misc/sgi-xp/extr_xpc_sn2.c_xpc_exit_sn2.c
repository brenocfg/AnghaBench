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
 int /*<<< orphan*/  SGI_XPC_ACTIVATE ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xpc_disallow_IPI_ops_sn2 () ; 
 int /*<<< orphan*/  xpc_remote_copy_buffer_base_sn2 ; 

void
xpc_exit_sn2(void)
{
	free_irq(SGI_XPC_ACTIVATE, NULL);
	xpc_disallow_IPI_ops_sn2();
	kfree(xpc_remote_copy_buffer_base_sn2);
}