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
 int xencomm_arch_hypercall_console_io (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xencomm_is_initialized () ; 
 int /*<<< orphan*/  xencomm_map_no_alloc (char*,int) ; 

int
xencomm_hypercall_console_io(int cmd, int count, char *str)
{
	/* xen early printk uses console io hypercall before
	 * xencomm initialization. In that case, we just ignore it.
	 */
	if (!xencomm_is_initialized())
		return 0;

	return xencomm_arch_hypercall_console_io
		(cmd, count, xencomm_map_no_alloc(str, count));
}