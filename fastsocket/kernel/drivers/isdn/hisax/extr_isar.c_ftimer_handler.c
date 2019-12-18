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
struct BCState {int /*<<< orphan*/  Flag; TYPE_1__* cs; } ;
struct TYPE_2__ {scalar_t__ debug; } ;

/* Variables and functions */
 int /*<<< orphan*/  BC_FLG_FTI_FTS ; 
 int /*<<< orphan*/  BC_FLG_FTI_RUN ; 
 int /*<<< orphan*/  BC_FLG_LL_CONN ; 
 int /*<<< orphan*/  B_LL_CONNECT ; 
 int /*<<< orphan*/  B_LL_OK ; 
 int /*<<< orphan*/  debugl1 (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_event (struct BCState*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ftimer_handler(struct BCState *bcs) {
	if (bcs->cs->debug)
		debugl1(bcs->cs, "ftimer flags %04x",
			bcs->Flag);
	test_and_clear_bit(BC_FLG_FTI_RUN, &bcs->Flag);
	if (test_and_clear_bit(BC_FLG_LL_CONN, &bcs->Flag)) {
		schedule_event(bcs, B_LL_CONNECT);
	}
	if (test_and_clear_bit(BC_FLG_FTI_FTS, &bcs->Flag)) {
		schedule_event(bcs, B_LL_OK);
	}
}