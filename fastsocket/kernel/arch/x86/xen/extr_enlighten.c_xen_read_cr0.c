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
 unsigned long native_read_cr0 () ; 
 unsigned long percpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  percpu_write (int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  xen_cr0_value ; 

__attribute__((used)) static unsigned long xen_read_cr0(void)
{
	unsigned long cr0 = percpu_read(xen_cr0_value);

	if (unlikely(cr0 == 0)) {
		cr0 = native_read_cr0();
		percpu_write(xen_cr0_value, cr0);
	}

	return cr0;
}