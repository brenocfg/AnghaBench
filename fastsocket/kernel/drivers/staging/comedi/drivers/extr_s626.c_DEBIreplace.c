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
typedef  int uint16_t ;
struct comedi_device {int dummy; } ;

/* Variables and functions */
 int DEBI_CMD_RDWORD ; 
 int DEBI_CMD_WRWORD ; 
 int /*<<< orphan*/  DEBItransfer (struct comedi_device*) ; 
 int /*<<< orphan*/  P_DEBIAD ; 
 int /*<<< orphan*/  P_DEBICMD ; 
 scalar_t__ RR7146 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR7146 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void DEBIreplace(struct comedi_device *dev, uint16_t addr, uint16_t mask,
			uint16_t wdata)
{

	/*  Copy target gate array register into P_DEBIAD register. */
	WR7146(P_DEBICMD, DEBI_CMD_RDWORD | addr);
	/* Set up DEBI control reg value in shadow RAM. */
	DEBItransfer(dev);	/*  Execute the DEBI Read transfer. */

	/*  Write back the modified image. */
	WR7146(P_DEBICMD, DEBI_CMD_WRWORD | addr);
	/* Set up DEBI control reg value in shadow  RAM. */

	WR7146(P_DEBIAD, wdata | ((uint16_t) RR7146(P_DEBIAD) & mask));
	/* Modify the register image. */
	DEBItransfer(dev);	/*  Execute the DEBI Write transfer. */
}