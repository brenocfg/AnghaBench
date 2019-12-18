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
 int /*<<< orphan*/  free_vm_area (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ghes_ioremap_area ; 

__attribute__((used)) static void ghes_ioremap_exit(void)
{
	free_vm_area(ghes_ioremap_area);
}