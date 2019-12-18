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
struct IsdnCardState {int debug; int /*<<< orphan*/  (* writeisac ) (struct IsdnCardState*,int /*<<< orphan*/ ,unsigned int) ;} ;

/* Variables and functions */
 int L1_DEB_ISAC ; 
 int /*<<< orphan*/  W_CIX ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,unsigned int) ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void
ph_command(struct IsdnCardState *cs, unsigned int command)
{
	if (cs->debug & L1_DEB_ISAC)
		debugl1(cs, "ph_command %x", command);
	cs->writeisac(cs, W_CIX, command);
}