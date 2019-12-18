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
struct FsmInst {struct Channel* userdata; } ;
struct Channel {int debug; scalar_t__ leased; } ;

/* Variables and functions */
 int /*<<< orphan*/  HL_LL (struct Channel*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISDN_STAT_DHUP ; 
 int /*<<< orphan*/  link_debug (struct Channel*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lli_close (struct FsmInst*) ; 
 int /*<<< orphan*/  lli_deliver_cause (struct Channel*) ; 
 int /*<<< orphan*/  lli_leased_hup (struct FsmInst*,struct Channel*) ; 

__attribute__((used)) static void
lli_dhup_close(struct FsmInst *fi, int event, void *arg)
{
	struct Channel *chanp = fi->userdata;

	if (chanp->leased) {
		lli_leased_hup(fi, chanp);
	} else {
		if (chanp->debug & 1)
			link_debug(chanp, 0, "STAT_DHUP");
		lli_deliver_cause(chanp);
		HL_LL(chanp, ISDN_STAT_DHUP);
		lli_close(fi);
	}
}