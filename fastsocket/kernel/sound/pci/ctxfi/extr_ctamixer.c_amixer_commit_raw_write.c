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
struct hw {int /*<<< orphan*/  (* amixer_commit_write ) (struct hw*,unsigned int,int /*<<< orphan*/ ) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  ctrl_blk; TYPE_1__* ops; struct hw* hw; } ;
struct amixer {TYPE_2__ rsc; } ;
struct TYPE_3__ {unsigned int (* output_slot ) (TYPE_2__*) ;} ;

/* Variables and functions */
 unsigned int stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (struct hw*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amixer_commit_raw_write(struct amixer *amixer)
{
	struct hw *hw;
	unsigned int index;

	hw = amixer->rsc.hw;
	index = amixer->rsc.ops->output_slot(&amixer->rsc);
	hw->amixer_commit_write(hw, index, amixer->rsc.ctrl_blk);

	return 0;
}