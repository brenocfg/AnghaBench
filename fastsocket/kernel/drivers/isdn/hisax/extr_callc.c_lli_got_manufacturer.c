#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ MFlag; } ;
struct TYPE_6__ {TYPE_1__ elsa; } ;
struct IsdnCardState {scalar_t__ typ; int /*<<< orphan*/  (* cardmsg ) (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_2__ hw; } ;
struct Channel {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  para; } ;
typedef  TYPE_3__ capi_msg ;

/* Variables and functions */
 int /*<<< orphan*/  CARD_AUX_IND ; 
 scalar_t__ ISDN_CTYPE_ELSA ; 
 scalar_t__ ISDN_CTYPE_ELSA_PCI ; 
 scalar_t__ ISDN_CTYPE_ELSA_PNP ; 
 int /*<<< orphan*/  stub1 (struct IsdnCardState*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
lli_got_manufacturer(struct Channel *chanp, struct IsdnCardState *cs, capi_msg *cm) {
	if ((cs->typ == ISDN_CTYPE_ELSA) || (cs->typ == ISDN_CTYPE_ELSA_PNP) ||
		(cs->typ == ISDN_CTYPE_ELSA_PCI)) {
		if (cs->hw.elsa.MFlag) {
			cs->cardmsg(cs, CARD_AUX_IND, cm->para);
		}
	}
}