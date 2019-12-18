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
struct TYPE_2__ {int /*<<< orphan*/  bas; } ;
struct cardstate {int /*<<< orphan*/  bcs; TYPE_1__ hw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BAS_TIMEOUT ; 
 int /*<<< orphan*/  BS_RESETTING ; 
 int /*<<< orphan*/  HD_RESET_INTERRUPT_PIPE ; 
 int /*<<< orphan*/  req_submit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_basstate (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void error_reset(struct cardstate *cs)
{
	/* reset interrupt pipe to recover (ignore errors) */
	update_basstate(cs->hw.bas, BS_RESETTING, 0);
	req_submit(cs->bcs, HD_RESET_INTERRUPT_PIPE, 0, BAS_TIMEOUT);
}