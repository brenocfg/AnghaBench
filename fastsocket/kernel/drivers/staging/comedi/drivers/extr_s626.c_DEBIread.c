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
 int /*<<< orphan*/  DEBItransfer (struct comedi_device*) ; 
 int /*<<< orphan*/  P_DEBIAD ; 
 int /*<<< orphan*/  P_DEBICMD ; 
 scalar_t__ RR7146 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WR7146 (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint16_t DEBIread(struct comedi_device *dev, uint16_t addr)
{
	uint16_t retval;

	/*  Set up DEBI control register value in shadow RAM. */
	WR7146(P_DEBICMD, DEBI_CMD_RDWORD | addr);

	/*  Execute the DEBI transfer. */
	DEBItransfer(dev);

	/*  Fetch target register value. */
	retval = (uint16_t) RR7146(P_DEBIAD);

	/*  Return register value. */
	return retval;
}