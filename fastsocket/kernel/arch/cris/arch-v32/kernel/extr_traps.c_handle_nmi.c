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
struct pt_regs {int dummy; } ;
struct TYPE_3__ {scalar_t__ ext; } ;
typedef  TYPE_1__ reg_intr_vect_r_nmi ;

/* Variables and functions */
 TYPE_1__ REG_RD (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  intr_vect ; 
 int /*<<< orphan*/  nmi_handler (struct pt_regs*) ; 
 int /*<<< orphan*/  r_nmi ; 
 int /*<<< orphan*/  regi_irq ; 
 scalar_t__ regk_intr_vect_on ; 

void handle_nmi(struct pt_regs *regs)
{
#ifdef CONFIG_ETRAXFS
	reg_intr_vect_r_nmi r;
#endif

	if (nmi_handler)
		nmi_handler(regs);

#ifdef CONFIG_ETRAXFS
	/* Wait until nmi is no longer active. */
	do {
		r = REG_RD(intr_vect, regi_irq, r_nmi);
	} while (r.ext == regk_intr_vect_on);
#endif
}