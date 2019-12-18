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
struct adapter {int flags; } ;
typedef  int /*<<< orphan*/  irq_handler_t ;

/* Variables and functions */
 int USING_MSI ; 
 int USING_MSIX ; 
 int /*<<< orphan*/  t4_intr_intx ; 
 int /*<<< orphan*/  t4_intr_msi ; 
 int /*<<< orphan*/  t4_sge_intr_msix ; 

irq_handler_t t4_intr_handler(struct adapter *adap)
{
	if (adap->flags & USING_MSIX)
		return t4_sge_intr_msix;
	if (adap->flags & USING_MSI)
		return t4_intr_msi;
	return t4_intr_intx;
}