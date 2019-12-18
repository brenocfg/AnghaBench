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
struct vm_fault {int /*<<< orphan*/  page; } ;
struct vm_area_struct {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia32_gate_page ; 

int
ia32_install_gate_page (struct vm_area_struct *vma, struct vm_fault *vmf)
{
	vmf->page = ia32_gate_page;
	get_page(vmf->page);
	return 0;
}