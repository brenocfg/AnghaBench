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
struct rsc {TYPE_1__* ops; } ;
struct hw {int /*<<< orphan*/  (* amixer_set_x ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* amixer_set_mode ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl_blk; struct hw* hw; } ;
struct amixer {TYPE_2__ rsc; struct rsc* input; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* output_slot ) (struct rsc*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AMIXER_Y_IMMEDIATE ; 
 int /*<<< orphan*/  BLANK_SLOT ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (struct rsc*) ; 

__attribute__((used)) static int amixer_set_input(struct amixer *amixer, struct rsc *rsc)
{
	struct hw *hw;

	hw = amixer->rsc.hw;
	hw->amixer_set_mode(amixer->rsc.ctrl_blk, AMIXER_Y_IMMEDIATE);
	amixer->input = rsc;
	if (!rsc)
		hw->amixer_set_x(amixer->rsc.ctrl_blk, BLANK_SLOT);
	else
		hw->amixer_set_x(amixer->rsc.ctrl_blk,
					rsc->ops->output_slot(rsc));

	return 0;
}