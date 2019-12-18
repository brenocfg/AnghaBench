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
struct TYPE_2__ {scalar_t__ intr_type; } ;
struct s2io_nic {TYPE_1__ config; } ;

/* Variables and functions */
 scalar_t__ MSI_X ; 
 int /*<<< orphan*/  remove_inta_isr (struct s2io_nic*) ; 
 int /*<<< orphan*/  remove_msix_isr (struct s2io_nic*) ; 

__attribute__((used)) static void s2io_rem_isr(struct s2io_nic *sp)
{
	if (sp->config.intr_type == MSI_X)
		remove_msix_isr(sp);
	else
		remove_inta_isr(sp);
}