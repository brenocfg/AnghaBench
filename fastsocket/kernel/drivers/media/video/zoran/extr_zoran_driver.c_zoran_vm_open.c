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
struct zoran_mapping {int /*<<< orphan*/  count; } ;
struct vm_area_struct {struct zoran_mapping* vm_private_data; } ;

/* Variables and functions */

__attribute__((used)) static void
zoran_vm_open (struct vm_area_struct *vma)
{
	struct zoran_mapping *map = vma->vm_private_data;

	map->count++;
}