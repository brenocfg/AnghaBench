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
struct TYPE_3__ {int /*<<< orphan*/  ph_state; } ;
struct TYPE_4__ {TYPE_1__ isac; } ;
struct IsdnCardState {int debug; int /*<<< orphan*/  (* writeisac ) (struct IsdnCardState*,int /*<<< orphan*/ ,unsigned int) ;TYPE_2__ dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPACX_CIX0 ; 
 int L1_DEB_ISAC ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void 
ph_command(struct IsdnCardState *cs, unsigned int command)
{
	if (cs->debug &L1_DEB_ISAC)
		debugl1(cs, "ph_command (%#x) in (%#x)", command,
			cs->dc.isac.ph_state);
//###################################  
//	printk(KERN_INFO "ph_command (%#x)\n", command);
//###################################  
	cs->writeisac(cs, IPACX_CIX0, (command << 4) | 0x0E);
}