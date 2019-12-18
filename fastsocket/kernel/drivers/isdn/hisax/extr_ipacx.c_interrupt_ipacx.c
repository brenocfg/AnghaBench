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
typedef  int u_char ;
struct IsdnCardState {int (* readisac ) (struct IsdnCardState*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  IPACX_ISTA ; 
 int /*<<< orphan*/  bch_int (struct IsdnCardState*,int) ; 
 int /*<<< orphan*/  cic_int (struct IsdnCardState*) ; 
 int /*<<< orphan*/  dch_int (struct IsdnCardState*) ; 
 int stub1 (struct IsdnCardState*,int /*<<< orphan*/ ) ; 

void 
interrupt_ipacx(struct IsdnCardState *cs)
{
	u_char ista;
  
	while ((ista = cs->readisac(cs, IPACX_ISTA))) {
//#################################################  
//		printk(KERN_WARNING "interrupt_ipacx(ista=%02x)\n", ista);
//#################################################  
    if (ista &0x80) bch_int(cs, 0); // B channel interrupts
    if (ista &0x40) bch_int(cs, 1);
    
    if (ista &0x01) dch_int(cs);    // D channel
    if (ista &0x10) cic_int(cs);    // Layer 1 state
  }  
}