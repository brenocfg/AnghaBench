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
struct TYPE_4__ {int /*<<< orphan*/  l2l1; } ;
struct TYPE_3__ {struct BCState* bcs; int /*<<< orphan*/  hardware; int /*<<< orphan*/  bc; } ;
struct PStack {TYPE_2__ l2; TYPE_1__ l1; } ;
struct BCState {struct PStack* st; int /*<<< orphan*/  channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  hfc_l2l1 ; 
 scalar_t__ open_hfcstate (int /*<<< orphan*/ ,struct BCState*) ; 
 int /*<<< orphan*/  setstack_l1_B (struct PStack*) ; 
 int /*<<< orphan*/  setstack_manager (struct PStack*) ; 

__attribute__((used)) static int
setstack_2b(struct PStack *st, struct BCState *bcs)
{
	bcs->channel = st->l1.bc;
	if (open_hfcstate(st->l1.hardware, bcs))
		return (-1);
	st->l1.bcs = bcs;
	st->l2.l2l1 = hfc_l2l1;
	setstack_manager(st);
	bcs->st = st;
	setstack_l1_B(st);
	return (0);
}