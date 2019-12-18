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
 unsigned long percpu_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xen_cr3 ; 

__attribute__((used)) static unsigned long xen_read_cr3(void)
{
	return percpu_read(xen_cr3);
}