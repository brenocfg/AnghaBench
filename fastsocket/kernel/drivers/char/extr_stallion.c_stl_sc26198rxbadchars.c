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
struct stlport {int dummy; } ;

/* Variables and functions */
 unsigned char CR_CLEARRXERR ; 
 int /*<<< orphan*/  MR1 ; 
 unsigned char MR1_ERRBLOCK ; 
 int /*<<< orphan*/  RXFIFO ; 
 int /*<<< orphan*/  SCCR ; 
 int /*<<< orphan*/  SR ; 
 unsigned char SR_RXRDY ; 
 void* stl_sc26198getreg (struct stlport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stl_sc26198rxbadch (struct stlport*,unsigned char,char) ; 
 int /*<<< orphan*/  stl_sc26198setreg (struct stlport*,int /*<<< orphan*/ ,unsigned char) ; 

__attribute__((used)) static void stl_sc26198rxbadchars(struct stlport *portp)
{
	unsigned char	status, mr1;
	char		ch;

/*
 *	To get the precise error type for each character we must switch
 *	back into CHAR error mode.
 */
	mr1 = stl_sc26198getreg(portp, MR1);
	stl_sc26198setreg(portp, MR1, (mr1 & ~MR1_ERRBLOCK));

	while ((status = stl_sc26198getreg(portp, SR)) & SR_RXRDY) {
		stl_sc26198setreg(portp, SCCR, CR_CLEARRXERR);
		ch = stl_sc26198getreg(portp, RXFIFO);
		stl_sc26198rxbadch(portp, status, ch);
	}

/*
 *	To get correct interrupt class we must switch back into BLOCK
 *	error mode.
 */
	stl_sc26198setreg(portp, MR1, mr1);
}