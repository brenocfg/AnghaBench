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
typedef  int /*<<< orphan*/  u8 ;
struct dp_state {int /*<<< orphan*/  aux; int /*<<< orphan*/  head; int /*<<< orphan*/  outp; int /*<<< orphan*/  disp; TYPE_1__* func; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* pattern ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPCD_LC02 ; 
 int /*<<< orphan*/  DPCD_LC02_TRAINING_PATTERN_SET ; 
 int /*<<< orphan*/  nv_rdaux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  nv_wraux (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dp_set_training_pattern(struct dp_state *dp, u8 pattern)
{
	u8 sink_tp;

	DBG("training pattern %d\n", pattern);
	dp->func->pattern(dp->disp, dp->outp, dp->head, pattern);

	nv_rdaux(dp->aux, DPCD_LC02, &sink_tp, 1);
	sink_tp &= ~DPCD_LC02_TRAINING_PATTERN_SET;
	sink_tp |= pattern;
	nv_wraux(dp->aux, DPCD_LC02, &sink_tp, 1);
}