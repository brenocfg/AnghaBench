#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_1__* ops; } ;
struct sum {TYPE_3__ rsc; } ;
struct hw {int /*<<< orphan*/  (* amixer_set_sadr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* amixer_set_se ) (int /*<<< orphan*/ ,int) ;} ;
struct TYPE_5__ {int /*<<< orphan*/  ctrl_blk; struct hw* hw; } ;
struct amixer {TYPE_2__ rsc; struct sum* sum; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* index ) (TYPE_3__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (TYPE_3__*) ; 

__attribute__((used)) static int amixer_set_sum(struct amixer *amixer, struct sum *sum)
{
	struct hw *hw;

	hw = amixer->rsc.hw;
	amixer->sum = sum;
	if (!sum) {
		hw->amixer_set_se(amixer->rsc.ctrl_blk, 0);
	} else {
		hw->amixer_set_se(amixer->rsc.ctrl_blk, 1);
		hw->amixer_set_sadr(amixer->rsc.ctrl_blk,
					sum->rsc.ops->index(&sum->rsc));
	}

	return 0;
}