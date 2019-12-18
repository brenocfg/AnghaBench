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
 int DEBI_CMD_WRWORD ; 
 int /*<<< orphan*/  DEBItransfer (struct comedi_device*) ; 
 int /*<<< orphan*/  P_DEBIAD ; 
 int /*<<< orphan*/  P_DEBICMD ; 
 int /*<<< orphan*/  WR7146 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void DEBIwrite(struct comedi_device *dev, uint16_t addr, uint16_t wdata)
{

	/*  Set up DEBI control register value in shadow RAM. */
	WR7146(P_DEBICMD, DEBI_CMD_WRWORD | addr);
	WR7146(P_DEBIAD, wdata);

	/*  Execute the DEBI transfer. */
	DEBItransfer(dev);
}