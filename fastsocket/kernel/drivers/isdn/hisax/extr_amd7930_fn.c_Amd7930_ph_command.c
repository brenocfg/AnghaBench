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
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_3__ {int /*<<< orphan*/  lmr1; } ;
struct TYPE_4__ {TYPE_1__ amd7930; } ;
struct IsdnCardState {int debug; TYPE_2__ dc; } ;

/* Variables and functions */
 int L1_DEB_ISAC ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wByteAMD (struct IsdnCardState*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
Amd7930_ph_command(struct IsdnCardState *cs, u_char command, char *s)
{
	if (cs->debug & L1_DEB_ISAC)
		debugl1(cs, "AMD7930: %s: ph_command 0x%02X", s, command);

        cs->dc.amd7930.lmr1 = command;
        wByteAMD(cs, 0xA3, command);
}