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
typedef  int u_int ;
struct IsdnCardState {scalar_t__ subtyp; scalar_t__ debug; } ;
struct BCState {int dummy; } ;

/* Variables and functions */
 scalar_t__ AVM_FRITZ_PCI ; 
 int HDLC_INT_MASK ; 
 int HDLC_INT_RPR ; 
 scalar_t__ HDLC_STATUS ; 
 int /*<<< orphan*/  HDLC_irq (struct BCState*,int) ; 
 int ReadHDLCPCI (struct IsdnCardState*,int,scalar_t__) ; 
 int ReadHDLCPnP (struct IsdnCardState*,int,scalar_t__) ; 
 struct BCState* Sel_BCS (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*) ; 

__attribute__((used)) static inline void
HDLC_irq_main(struct IsdnCardState *cs)
{
	u_int stat;
	struct BCState *bcs;

	if (cs->subtyp == AVM_FRITZ_PCI) {
		stat = ReadHDLCPCI(cs, 0, HDLC_STATUS);
	} else {
		stat = ReadHDLCPnP(cs, 0, HDLC_STATUS);
		if (stat & HDLC_INT_RPR)
			stat |= (ReadHDLCPnP(cs, 0, HDLC_STATUS+1))<<8;
	}
	if (stat & HDLC_INT_MASK) {
		if (!(bcs = Sel_BCS(cs, 0))) {
			if (cs->debug)
				debugl1(cs, "hdlc spurious channel 0 IRQ");
		} else
			HDLC_irq(bcs, stat);
	}
	if (cs->subtyp == AVM_FRITZ_PCI) {
		stat = ReadHDLCPCI(cs, 1, HDLC_STATUS);
	} else {
		stat = ReadHDLCPnP(cs, 1, HDLC_STATUS);
		if (stat & HDLC_INT_RPR)
			stat |= (ReadHDLCPnP(cs, 1, HDLC_STATUS+1))<<8;
	}
	if (stat & HDLC_INT_MASK) {
		if (!(bcs = Sel_BCS(cs, 1))) {
			if (cs->debug)
				debugl1(cs, "hdlc spurious channel 1 IRQ");
		} else
			HDLC_irq(bcs, stat);
	}
}