#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vm_page_t ;
typedef  int /*<<< orphan*/  ppnum_t ;
struct TYPE_4__ {int /*<<< orphan*/  vmp_fictitious; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  c_vm_page_grab_fictitious ; 
 int /*<<< orphan*/  c_vm_page_grab_fictitious_failed ; 
 int /*<<< orphan*/  vm_page_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vm_page_zone ; 
 scalar_t__ zget (int /*<<< orphan*/ ) ; 

vm_page_t
vm_page_grab_fictitious_common(
	ppnum_t phys_addr)
{
	vm_page_t	m;

	if ((m = (vm_page_t)zget(vm_page_zone))) {

		vm_page_init(m, phys_addr, FALSE);
		m->vmp_fictitious = TRUE;

		c_vm_page_grab_fictitious++;
	} else
		c_vm_page_grab_fictitious_failed++;

	return m;
}