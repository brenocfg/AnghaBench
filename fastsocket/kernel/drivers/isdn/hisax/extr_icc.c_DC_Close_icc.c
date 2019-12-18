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
struct TYPE_3__ {int /*<<< orphan*/ * mon_tx; int /*<<< orphan*/ * mon_rx; } ;
struct TYPE_4__ {TYPE_1__ icc; } ;
struct IsdnCardState {TYPE_2__ dc; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
DC_Close_icc(struct IsdnCardState *cs) {
	kfree(cs->dc.icc.mon_rx);
	cs->dc.icc.mon_rx = NULL;
	kfree(cs->dc.icc.mon_tx);
	cs->dc.icc.mon_tx = NULL;
}