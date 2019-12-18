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
struct isac {unsigned char (* read_isac ) (struct isac*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_isac ) (struct isac*,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DBG_IRQ ; 
 int /*<<< orphan*/  DBG_WARN ; 
 int /*<<< orphan*/  ISAC_ISTA ; 
 unsigned char ISAC_ISTA_CISQ ; 
 unsigned char ISAC_ISTA_EXI ; 
 unsigned char ISAC_ISTA_RME ; 
 unsigned char ISAC_ISTA_RPF ; 
 unsigned char ISAC_ISTA_RSC ; 
 unsigned char ISAC_ISTA_SIN ; 
 unsigned char ISAC_ISTA_XPR ; 
 int /*<<< orphan*/  ISAC_MASK ; 
 int /*<<< orphan*/  isac_cisq_interrupt (struct isac*) ; 
 int /*<<< orphan*/  isac_empty_fifo (struct isac*,int) ; 
 int /*<<< orphan*/  isac_exi_interrupt (struct isac*) ; 
 int /*<<< orphan*/  isac_rme_interrupt (struct isac*) ; 
 int /*<<< orphan*/  isac_xpr_interrupt (struct isac*) ; 
 unsigned char stub1 (struct isac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct isac*,int /*<<< orphan*/ ,int) ; 

void isac_irq(struct isac *isac)
{
	unsigned char val;

	val = isac->read_isac(isac, ISAC_ISTA);
	DBG(DBG_IRQ, "ISTA %#x", val);

	if (val & ISAC_ISTA_EXI) {
		DBG(DBG_IRQ, "EXI");
		isac_exi_interrupt(isac);
	}
	if (val & ISAC_ISTA_XPR) {
		DBG(DBG_IRQ, "XPR");
		isac_xpr_interrupt(isac);
	}
	if (val & ISAC_ISTA_RME) {
		DBG(DBG_IRQ, "RME");
		isac_rme_interrupt(isac);
	}
	if (val & ISAC_ISTA_RPF) {
		DBG(DBG_IRQ, "RPF");
		isac_empty_fifo(isac, 0x20);
	}
	if (val & ISAC_ISTA_CISQ) {
		DBG(DBG_IRQ, "CISQ");
		isac_cisq_interrupt(isac);
	}
	if (val & ISAC_ISTA_RSC) {
		DBG(DBG_WARN, "RSC");
	}
	if (val & ISAC_ISTA_SIN) {
		DBG(DBG_WARN, "SIN");
	}
	isac->write_isac(isac, ISAC_MASK, 0xff);
	isac->write_isac(isac, ISAC_MASK, 0x00);
}