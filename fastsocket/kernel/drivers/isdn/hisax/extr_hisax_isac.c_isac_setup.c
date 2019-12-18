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
struct isac {int mocr; int adf2; int (* read_isac ) (struct isac*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* write_isac ) (struct isac*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  l1m; int /*<<< orphan*/  flags; int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (int,char*,int) ; 
 int /*<<< orphan*/  FsmEvent (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ISAC_ADF1 ; 
 int /*<<< orphan*/  ISAC_ADF2 ; 
 int /*<<< orphan*/  ISAC_CIR0 ; 
 int /*<<< orphan*/  ISAC_CMDR ; 
 int ISAC_CMDR_RRES ; 
 int ISAC_CMDR_XRES ; 
 int /*<<< orphan*/  ISAC_CMD_RES ; 
 int /*<<< orphan*/  ISAC_EXIR ; 
 int /*<<< orphan*/  ISAC_IOM1 ; 
 int /*<<< orphan*/  ISAC_ISTA ; 
 int /*<<< orphan*/  ISAC_MASK ; 
 int /*<<< orphan*/  ISAC_MODE ; 
 int /*<<< orphan*/  ISAC_SPCR ; 
 int /*<<< orphan*/  ISAC_SQXR ; 
 int /*<<< orphan*/  ISAC_STAR ; 
 int /*<<< orphan*/  ISAC_STCR ; 
 int /*<<< orphan*/  ISAC_TIMR ; 
 int /*<<< orphan*/  TYPE_ISAC ; 
 int /*<<< orphan*/  isac_version (struct isac*) ; 
 int /*<<< orphan*/  ph_command (struct isac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub10 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub11 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub12 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub13 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int stub14 (struct isac*,int /*<<< orphan*/ ) ; 
 int stub15 (struct isac*,int /*<<< orphan*/ ) ; 
 int stub16 (struct isac*,int /*<<< orphan*/ ) ; 
 int stub17 (struct isac*,int /*<<< orphan*/ ) ; 
 int stub18 (struct isac*,int /*<<< orphan*/ ) ; 
 int stub19 (struct isac*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub20 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub21 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub6 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub7 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub8 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub9 (struct isac*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void isac_setup(struct isac *isac)
{
	int val, eval;

	isac->type = TYPE_ISAC;
	isac_version(isac);

	ph_command(isac, ISAC_CMD_RES);

  	isac->write_isac(isac, ISAC_MASK, 0xff);
  	isac->mocr = 0xaa;
	if (test_bit(ISAC_IOM1, &isac->flags)) {
		/* IOM 1 Mode */
		isac->write_isac(isac, ISAC_ADF2, 0x0);
		isac->write_isac(isac, ISAC_SPCR, 0xa);
		isac->write_isac(isac, ISAC_ADF1, 0x2);
		isac->write_isac(isac, ISAC_STCR, 0x70);
		isac->write_isac(isac, ISAC_MODE, 0xc9);
	} else {
		/* IOM 2 Mode */
		if (!isac->adf2)
			isac->adf2 = 0x80;
		isac->write_isac(isac, ISAC_ADF2, isac->adf2);
		isac->write_isac(isac, ISAC_SQXR, 0x2f);
		isac->write_isac(isac, ISAC_SPCR, 0x00);
		isac->write_isac(isac, ISAC_STCR, 0x70);
		isac->write_isac(isac, ISAC_MODE, 0xc9);
		isac->write_isac(isac, ISAC_TIMR, 0x00);
		isac->write_isac(isac, ISAC_ADF1, 0x00);
	}
	val = isac->read_isac(isac, ISAC_STAR);
	DBG(2, "ISAC STAR %x", val);
	val = isac->read_isac(isac, ISAC_MODE);
	DBG(2, "ISAC MODE %x", val);
	val = isac->read_isac(isac, ISAC_ADF2);
	DBG(2, "ISAC ADF2 %x", val);
	val = isac->read_isac(isac, ISAC_ISTA);
	DBG(2, "ISAC ISTA %x", val);
	if (val & 0x01) {
		eval = isac->read_isac(isac, ISAC_EXIR);
		DBG(2, "ISAC EXIR %x", eval);
	}
	val = isac->read_isac(isac, ISAC_CIR0);
	DBG(2, "ISAC CIR0 %x", val);
	FsmEvent(&isac->l1m, (val >> 2) & 0xf, NULL);

	isac->write_isac(isac, ISAC_MASK, 0x0);
	// RESET Receiver and Transmitter
	isac->write_isac(isac, ISAC_CMDR, ISAC_CMDR_XRES | ISAC_CMDR_RRES);
}