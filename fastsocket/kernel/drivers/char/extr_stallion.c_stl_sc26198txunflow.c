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
struct tty_struct {int dummy; } ;
struct stlport {int /*<<< orphan*/  istate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASYI_TXFLOWED ; 
 unsigned char CR_HOSTXON ; 
 int /*<<< orphan*/  MR0 ; 
 unsigned char MR0_SWFRXTX ; 
 int /*<<< orphan*/  SCCR ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned char stl_sc26198getreg (struct stlport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stl_sc26198setreg (struct stlport*,int /*<<< orphan*/ ,unsigned char) ; 
 int /*<<< orphan*/  stl_sc26198wait (struct stlport*) ; 

__attribute__((used)) static void stl_sc26198txunflow(struct stlport *portp, struct tty_struct *tty)
{
	unsigned char	mr0;

	mr0 = stl_sc26198getreg(portp, MR0);
	stl_sc26198setreg(portp, MR0, (mr0 & ~MR0_SWFRXTX));
	stl_sc26198setreg(portp, SCCR, CR_HOSTXON);
	stl_sc26198wait(portp);
	stl_sc26198setreg(portp, MR0, mr0);
	clear_bit(ASYI_TXFLOWED, &portp->istate);
}