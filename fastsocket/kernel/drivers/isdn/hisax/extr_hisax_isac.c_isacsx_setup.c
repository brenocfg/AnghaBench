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
struct isac {int /*<<< orphan*/  (* write_isac ) (struct isac*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int ISACSX_ISTA_CIC ; 
 int ISACSX_ISTA_ICD ; 
 int /*<<< orphan*/  ISACSX_MASK ; 
 int /*<<< orphan*/  ISACSX_MASKD ; 
 int /*<<< orphan*/  ISACSX_MODED ; 
 int /*<<< orphan*/  ISACSX_TR_CONF0 ; 
 int /*<<< orphan*/  ISACSX_TR_CONF2 ; 
 int /*<<< orphan*/  TYPE_ISACSX ; 
 int /*<<< orphan*/  stub1 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub4 (struct isac*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub5 (struct isac*,int /*<<< orphan*/ ,int) ; 

void isacsx_setup(struct isac *isac)
{
	isac->type = TYPE_ISACSX;
	// clear LDD
	isac->write_isac(isac, ISACSX_TR_CONF0, 0x00);
	// enable transmitter
	isac->write_isac(isac, ISACSX_TR_CONF2, 0x00);
	// transparent mode 0, RAC, stop/go
	isac->write_isac(isac, ISACSX_MODED,    0xc9);
	// all HDLC IRQ unmasked
	isac->write_isac(isac, ISACSX_MASKD,    0x03);
	// unmask ICD, CID IRQs
	isac->write_isac(isac, ISACSX_MASK,            
			 ~(ISACSX_ISTA_ICD | ISACSX_ISTA_CIC));
}