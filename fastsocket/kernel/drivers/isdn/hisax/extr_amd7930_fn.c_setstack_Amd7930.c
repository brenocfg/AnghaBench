#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  l1hw; } ;
struct PStack {TYPE_1__ l1; } ;
struct IsdnCardState {int debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  Amd7930_l1hw ; 
 int L1_DEB_ISAC ; 
 int /*<<< orphan*/  debugl1 (struct IsdnCardState*,char*) ; 

__attribute__((used)) static void
setstack_Amd7930(struct PStack *st, struct IsdnCardState *cs)
{

        if (cs->debug & L1_DEB_ISAC)
		debugl1(cs, "Amd7930: setstack called");

        st->l1.l1hw = Amd7930_l1hw;
}