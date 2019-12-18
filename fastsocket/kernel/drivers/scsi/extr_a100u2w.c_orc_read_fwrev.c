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
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct orc_host {scalar_t__ base; } ;

/* Variables and functions */
 int /*<<< orphan*/  HDO ; 
 int /*<<< orphan*/  ORC_CMD_VERSION ; 
 scalar_t__ ORC_HCTRL ; 
 scalar_t__ ORC_HDATA ; 
 scalar_t__ ORC_HSTUS ; 
 int inb (scalar_t__) ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ wait_HDO_off (struct orc_host*) ; 
 scalar_t__ wait_hdi_set (struct orc_host*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned short orc_read_fwrev(struct orc_host * host)
{
	u16 version;
	u8 data;

	outb(ORC_CMD_VERSION, host->base + ORC_HDATA);
	outb(HDO, host->base + ORC_HCTRL);
	if (wait_HDO_off(host) == 0)	/* Wait HDO off   */
		return 0;

	if (wait_hdi_set(host, &data) == 0)	/* Wait HDI set   */
		return 0;
	version = inb(host->base + ORC_HDATA);
	outb(data, host->base + ORC_HSTUS);	/* Clear HDI            */

	if (wait_hdi_set(host, &data) == 0)	/* Wait HDI set   */
		return 0;
	version |= inb(host->base + ORC_HDATA) << 8;
	outb(data, host->base + ORC_HSTUS);	/* Clear HDI            */

	return version;
}