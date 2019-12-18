#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct io7 {TYPE_2__* csrs; } ;
struct TYPE_4__ {TYPE_1__* PO7_LSI_CTL; } ;
struct TYPE_3__ {unsigned long csr; } ;

/* Variables and functions */
 int /*<<< orphan*/  mb () ; 

__attribute__((used)) static void 
io7_redirect_one_lsi(struct io7 *io7, unsigned int which, unsigned int where)
{
	unsigned long val;

	/*
	 * LSI_CTL has target PID @ 14
	 */
	val = io7->csrs->PO7_LSI_CTL[which].csr;
	val &= ~(0x1ffUL << 14);		/* clear the target pid */
	val |= ((unsigned long)where << 14);	/* set the new target pid */

	io7->csrs->PO7_LSI_CTL[which].csr = val;
	mb();
	io7->csrs->PO7_LSI_CTL[which].csr;
}