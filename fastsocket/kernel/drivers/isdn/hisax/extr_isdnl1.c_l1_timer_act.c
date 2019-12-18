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
struct TYPE_2__ {int /*<<< orphan*/  hardware; int /*<<< orphan*/  Flags; } ;
struct PStack {TYPE_1__ l1; } ;
struct FsmInst {struct PStack* userdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLG_L1_ACTIVATED ; 
 int /*<<< orphan*/  FLG_L1_ACTTIMER ; 
 int /*<<< orphan*/  L1activated (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
l1_timer_act(struct FsmInst *fi, int event, void *arg)
{
	struct PStack *st = fi->userdata;
	
	test_and_clear_bit(FLG_L1_ACTTIMER, &st->l1.Flags);
	test_and_set_bit(FLG_L1_ACTIVATED, &st->l1.Flags);
	L1activated(st->l1.hardware);
}