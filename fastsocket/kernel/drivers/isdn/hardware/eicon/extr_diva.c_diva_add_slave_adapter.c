#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  link; } ;
typedef  TYPE_1__ diva_os_xdi_adapter_t ;
typedef  int /*<<< orphan*/  diva_os_spin_lock_magic_t ;

/* Variables and functions */
 int /*<<< orphan*/  adapter_lock ; 
 int /*<<< orphan*/  adapter_queue ; 
 int /*<<< orphan*/  diva_os_enter_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  diva_os_leave_spin_lock (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void diva_add_slave_adapter(diva_os_xdi_adapter_t * a)
{
	diva_os_spin_lock_magic_t old_irql;

	diva_os_enter_spin_lock(&adapter_lock, &old_irql, "add_slave");
	list_add_tail(&a->link, &adapter_queue);
	diva_os_leave_spin_lock(&adapter_lock, &old_irql, "add_slave");
}