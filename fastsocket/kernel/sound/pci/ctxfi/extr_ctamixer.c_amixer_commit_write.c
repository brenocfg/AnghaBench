#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_3__* ops; } ;
struct sum {TYPE_4__ rsc; } ;
struct rsc {TYPE_2__* ops; } ;
struct hw {int /*<<< orphan*/  (* amixer_commit_write ) (struct hw*,unsigned int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* amixer_set_sadr ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* amixer_set_x ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* amixer_set_dirty_all ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_16__ {int msr; TYPE_1__* ops; int /*<<< orphan*/  ctrl_blk; struct hw* hw; } ;
struct amixer {TYPE_7__ rsc; struct sum* sum; struct rsc* input; } ;
struct TYPE_14__ {int /*<<< orphan*/  (* master ) (TYPE_4__*) ;int /*<<< orphan*/  (* next_conj ) (TYPE_4__*) ;int /*<<< orphan*/  (* index ) (TYPE_4__*) ;} ;
struct TYPE_13__ {int /*<<< orphan*/  (* master ) (struct rsc*) ;int /*<<< orphan*/  (* next_conj ) (struct rsc*) ;int /*<<< orphan*/  (* output_slot ) (struct rsc*) ;} ;
struct TYPE_12__ {unsigned int (* output_slot ) (TYPE_7__*) ;int /*<<< orphan*/  (* master ) (TYPE_7__*) ;int /*<<< orphan*/  (* next_conj ) (TYPE_7__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub10 (TYPE_4__*) ; 
 unsigned int stub11 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub12 (struct hw*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub13 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub14 (TYPE_7__*) ; 
 int /*<<< orphan*/  stub15 (struct rsc*) ; 
 int /*<<< orphan*/  stub16 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (struct rsc*) ; 
 int /*<<< orphan*/  stub3 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (struct rsc*) ; 
 int /*<<< orphan*/  stub7 (struct rsc*) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub9 (TYPE_4__*) ; 

__attribute__((used)) static int amixer_commit_write(struct amixer *amixer)
{
	struct hw *hw;
	unsigned int index;
	int i;
	struct rsc *input;
	struct sum *sum;

	hw = amixer->rsc.hw;
	input = amixer->input;
	sum = amixer->sum;

	/* Program master and conjugate resources */
	amixer->rsc.ops->master(&amixer->rsc);
	if (input)
		input->ops->master(input);

	if (sum)
		sum->rsc.ops->master(&sum->rsc);

	for (i = 0; i < amixer->rsc.msr; i++) {
		hw->amixer_set_dirty_all(amixer->rsc.ctrl_blk);
		if (input) {
			hw->amixer_set_x(amixer->rsc.ctrl_blk,
						input->ops->output_slot(input));
			input->ops->next_conj(input);
		}
		if (sum) {
			hw->amixer_set_sadr(amixer->rsc.ctrl_blk,
						sum->rsc.ops->index(&sum->rsc));
			sum->rsc.ops->next_conj(&sum->rsc);
		}
		index = amixer->rsc.ops->output_slot(&amixer->rsc);
		hw->amixer_commit_write(hw, index, amixer->rsc.ctrl_blk);
		amixer->rsc.ops->next_conj(&amixer->rsc);
	}
	amixer->rsc.ops->master(&amixer->rsc);
	if (input)
		input->ops->master(input);

	if (sum)
		sum->rsc.ops->master(&sum->rsc);

	return 0;
}