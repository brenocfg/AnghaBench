#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ base; int /*<<< orphan*/  isac; int /*<<< orphan*/  ale; scalar_t__ cfg; scalar_t__ ctrl; int /*<<< orphan*/  tl; } ;
struct TYPE_4__ {TYPE_1__ elsa; } ;
struct IsdnCardState {scalar_t__ subtyp; TYPE_2__ hw; } ;

/* Variables and functions */
 scalar_t__ ELSA_PCF ; 
 scalar_t__ ELSA_PCFPRO ; 
 scalar_t__ ELSA_PCMCIA_IPAC ; 
 scalar_t__ ELSA_QS1000PCI ; 
 scalar_t__ ELSA_QS3000 ; 
 scalar_t__ ELSA_QS3000PCI ; 
 int /*<<< orphan*/  IPAC_ATX ; 
 int /*<<< orphan*/  byteout (scalar_t__,int) ; 
 int /*<<< orphan*/  clear_arcofi (struct IsdnCardState*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_modem (struct IsdnCardState*) ; 
 int /*<<< orphan*/  release_region (scalar_t__,int) ; 
 int /*<<< orphan*/  writereg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
release_io_elsa(struct IsdnCardState *cs)
{
	int bytecnt = 8;

	del_timer(&cs->hw.elsa.tl);
#if ARCOFI_USE
	clear_arcofi(cs);
#endif
	if (cs->hw.elsa.ctrl)
		byteout(cs->hw.elsa.ctrl, 0);	/* LEDs Out */
	if (cs->subtyp == ELSA_QS1000PCI) {
		byteout(cs->hw.elsa.cfg + 0x4c, 0x01);  /* disable IRQ */
		writereg(cs->hw.elsa.ale, cs->hw.elsa.isac, IPAC_ATX, 0xff);
		bytecnt = 2;
		release_region(cs->hw.elsa.cfg, 0x80);
	}
	if (cs->subtyp == ELSA_QS3000PCI) {
		byteout(cs->hw.elsa.cfg + 0x4c, 0x03); /* disable ELSA PCI IRQ */
		writereg(cs->hw.elsa.ale, cs->hw.elsa.isac, IPAC_ATX, 0xff);
		release_region(cs->hw.elsa.cfg, 0x80);
	}
 	if (cs->subtyp == ELSA_PCMCIA_IPAC) {
		writereg(cs->hw.elsa.ale, cs->hw.elsa.isac, IPAC_ATX, 0xff);
 	}
	if ((cs->subtyp == ELSA_PCFPRO) ||
		(cs->subtyp == ELSA_QS3000) ||
		(cs->subtyp == ELSA_PCF) ||
		(cs->subtyp == ELSA_QS3000PCI)) {
		bytecnt = 16;
#if ARCOFI_USE
		release_modem(cs);
#endif
	}
	if (cs->hw.elsa.base)
		release_region(cs->hw.elsa.base, bytecnt);
}