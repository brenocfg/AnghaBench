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
struct vm_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_vm_area (struct vm_struct*) ; 
 int /*<<< orphan*/  kfree (struct vm_struct**) ; 

void pcpu_free_vm_areas(struct vm_struct **vms, int nr_vms)
{
	int i;

	for (i = 0; i < nr_vms; i++)
		free_vm_area(vms[i]);
	kfree(vms);
}