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
struct be_adapter {scalar_t__ eeh_error; } ;

/* Variables and functions */
 int be_cmd_intr_set (struct be_adapter*,int) ; 
 int /*<<< orphan*/  be_reg_intr_set (struct be_adapter*,int) ; 
 scalar_t__ lancer_chip (struct be_adapter*) ; 

__attribute__((used)) static void be_intr_set(struct be_adapter *adapter, bool enable)
{
	int status = 0;

	/* On lancer interrupts can't be controlled via this register */
	if (lancer_chip(adapter))
		return;

	if (adapter->eeh_error)
		return;

	status = be_cmd_intr_set(adapter, enable);
	if (status)
		be_reg_intr_set(adapter, enable);
}