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
 int /*<<< orphan*/  c_master_lock ; 
 int /*<<< orphan*/  lck_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_attr_setdefault (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_grp_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lck_rw_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vm_compressor_lck_attr ; 
 int /*<<< orphan*/  vm_compressor_lck_grp ; 
 int /*<<< orphan*/  vm_compressor_lck_grp_attr ; 

void
vm_compressor_init_locks(void)
{
	lck_grp_attr_setdefault(&vm_compressor_lck_grp_attr);
	lck_grp_init(&vm_compressor_lck_grp, "vm_compressor", &vm_compressor_lck_grp_attr);
	lck_attr_setdefault(&vm_compressor_lck_attr);

	lck_rw_init(&c_master_lock, &vm_compressor_lck_grp, &vm_compressor_lck_attr);
}