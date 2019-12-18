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
typedef  int /*<<< orphan*/  u32 ;
struct vm_area_struct {int /*<<< orphan*/  vm_end; int /*<<< orphan*/  vm_start; scalar_t__ vm_private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ehca_gen_dbg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehca_gen_err (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ehca_mm_close(struct vm_area_struct *vma)
{
	u32 *count = (u32 *)vma->vm_private_data;
	if (!count) {
		ehca_gen_err("Invalid vma struct vm_start=%lx vm_end=%lx",
			     vma->vm_start, vma->vm_end);
		return;
	}
	(*count)--;
	ehca_gen_dbg("vm_start=%lx vm_end=%lx count=%x",
		     vma->vm_start, vma->vm_end, *count);
}