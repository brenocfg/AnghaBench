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
struct isac {unsigned char (* read_isac ) (struct isac*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_isac ) (struct isac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  DBG_IRQ ; 
 int /*<<< orphan*/  DBG_WARN ; 
 int /*<<< orphan*/  ISACSX_CMDRD ; 
 int /*<<< orphan*/  ISACSX_CMDRD_RMC ; 
 int /*<<< orphan*/  ISACSX_ISTAD ; 
 unsigned char ISACSX_ISTAD_RFO ; 
 unsigned char ISACSX_ISTAD_RME ; 
 unsigned char ISACSX_ISTAD_RPF ; 
 unsigned char ISACSX_ISTAD_XDU ; 
 unsigned char ISACSX_ISTAD_XMR ; 
 unsigned char ISACSX_ISTAD_XPR ; 
 int /*<<< orphan*/  isac_empty_fifo (struct isac*,int) ; 
 int /*<<< orphan*/  isac_retransmit (struct isac*) ; 
 int /*<<< orphan*/  isacsx_rme_interrupt (struct isac*) ; 
 int /*<<< orphan*/  isacsx_xpr_interrupt (struct isac*) ; 
 unsigned char stub1 (struct isac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct isac*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void isacsx_icd_interrupt(struct isac *isac)
{
	unsigned char val;

	val = isac->read_isac(isac, ISACSX_ISTAD);
	DBG(DBG_IRQ, "ISTAD %#x", val);
	if (val & ISACSX_ISTAD_XDU) {
		DBG(DBG_WARN, "ISTAD XDU");
		isac_retransmit(isac);
	}
	if (val & ISACSX_ISTAD_XMR) {
		DBG(DBG_WARN, "ISTAD XMR");
		isac_retransmit(isac);
	}
	if (val & ISACSX_ISTAD_XPR) {
		DBG(DBG_IRQ, "ISTAD XPR");
		isacsx_xpr_interrupt(isac);
	}
	if (val & ISACSX_ISTAD_RFO) {
		DBG(DBG_WARN, "ISTAD RFO");
		isac->write_isac(isac, ISACSX_CMDRD, ISACSX_CMDRD_RMC);
	}
	if (val & ISACSX_ISTAD_RME) {
		DBG(DBG_IRQ, "ISTAD RME");
		isacsx_rme_interrupt(isac);
	}
	if (val & ISACSX_ISTAD_RPF) {
		DBG(DBG_IRQ, "ISTAD RPF");
		isac_empty_fifo(isac, 0x20);
	}
}