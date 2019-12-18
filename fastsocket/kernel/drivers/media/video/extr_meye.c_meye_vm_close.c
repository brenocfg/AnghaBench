#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {scalar_t__ vm_private_data; } ;
struct TYPE_2__ {int /*<<< orphan*/ * vma_use_count; } ;

/* Variables and functions */
 TYPE_1__ meye ; 

__attribute__((used)) static void meye_vm_close(struct vm_area_struct *vma)
{
	long idx = (long)vma->vm_private_data;
	meye.vma_use_count[idx]--;
}