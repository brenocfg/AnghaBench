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
struct orc_scb {unsigned char scbidx; } ;
struct orc_host {scalar_t__ base; } ;

/* Variables and functions */
 unsigned char HDO ; 
 unsigned char ORC_CMD_ABORT_SCB ; 
 scalar_t__ ORC_HCTRL ; 
 scalar_t__ ORC_HDATA ; 
 scalar_t__ ORC_HSTUS ; 
 unsigned char inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (unsigned char,scalar_t__) ; 
 scalar_t__ wait_HDO_off (struct orc_host*) ; 
 scalar_t__ wait_hdi_set (struct orc_host*,unsigned char*) ; 

__attribute__((used)) static int orchid_abort_scb(struct orc_host * host, struct orc_scb * scb)
{
	unsigned char data, status;

	outb(ORC_CMD_ABORT_SCB, host->base + ORC_HDATA);	/* Write command */
	outb(HDO, host->base + ORC_HCTRL);
	if (wait_HDO_off(host) == 0)	/* Wait HDO off   */
		return 0;

	outb(scb->scbidx, host->base + ORC_HDATA);	/* Write address */
	outb(HDO, host->base + ORC_HCTRL);
	if (wait_HDO_off(host) == 0)	/* Wait HDO off   */
		return 0;

	if (wait_hdi_set(host, &data) == 0)	/* Wait HDI set   */
		return 0;
	status = inb(host->base + ORC_HDATA);
	outb(data, host->base + ORC_HSTUS);	/* Clear HDI    */

	if (status == 1)	/* 0 - Successfully               */
		return 0;	/* 1 - Fail                     */
	return 1;
}