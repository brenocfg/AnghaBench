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
struct TYPE_3__ {int /*<<< orphan*/ * transbuf; int /*<<< orphan*/ * rcvbuf; scalar_t__ MFlag; } ;
struct TYPE_4__ {TYPE_1__ elsa; } ;
struct IsdnCardState {TYPE_2__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mshutdown (struct IsdnCardState*) ; 

__attribute__((used)) static void
release_modem(struct IsdnCardState *cs) {

	cs->hw.elsa.MFlag = 0;
	if (cs->hw.elsa.transbuf) {
		if (cs->hw.elsa.rcvbuf) {
			mshutdown(cs);
			kfree(cs->hw.elsa.rcvbuf);
			cs->hw.elsa.rcvbuf = NULL;
		}
		kfree(cs->hw.elsa.transbuf);
		cs->hw.elsa.transbuf = NULL;
	}
}