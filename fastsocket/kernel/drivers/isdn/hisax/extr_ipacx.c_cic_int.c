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
typedef  int u_char ;
struct TYPE_3__ {int ph_state; } ;
struct TYPE_4__ {TYPE_1__ isac; } ;
struct IsdnCardState {int (* readisac ) (struct IsdnCardState*,int /*<<< orphan*/ ) ;int debug; TYPE_2__ dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_L1STATECHANGE ; 
 int /*<<< orphan*/  IPACX_CIR0 ; 
 int L1_DEB_ISAC ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,int) ; 
 int /*<<< orphan*/  schedule_event (struct IsdnCardState*,int /*<<< orphan*/ ) ; 
 int stub1 (struct IsdnCardState*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void 
cic_int(struct IsdnCardState *cs)
{
	u_char event;

	event = cs->readisac(cs, IPACX_CIR0) >> 4;
	if (cs->debug &L1_DEB_ISAC) debugl1(cs, "cic_int(event=%#x)", event);
//#########################################  
//	printk(KERN_INFO "cic_int(%x)\n", event);
//#########################################  
  cs->dc.isac.ph_state = event;
  schedule_event(cs, D_L1STATECHANGE);
}