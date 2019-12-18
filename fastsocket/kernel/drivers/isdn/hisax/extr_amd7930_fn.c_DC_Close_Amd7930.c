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
struct IsdnCardState {int debug; } ;

/* Variables and functions */
 int L1_DEB_ISAC ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*) ; 

__attribute__((used)) static void
DC_Close_Amd7930(struct IsdnCardState *cs) {
        if (cs->debug & L1_DEB_ISAC)
		debugl1(cs, "Amd7930: DC_Close called");
}