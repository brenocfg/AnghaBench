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
struct sym_tcb {int dummy; } ;
struct sym_hcb {int dummy; } ;
struct sym_ccb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS_BUSY ; 
 int /*<<< orphan*/  HS_PRT ; 
 int /*<<< orphan*/  OUTB (struct sym_hcb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sym_nego_default (struct sym_hcb*,struct sym_tcb*,struct sym_ccb*) ; 

__attribute__((used)) static void sym_nego_rejected(struct sym_hcb *np, struct sym_tcb *tp, struct sym_ccb *cp)
{
	sym_nego_default(np, tp, cp);
	OUTB(np, HS_PRT, HS_BUSY);
}