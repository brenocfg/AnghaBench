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
struct TYPE_4__ {TYPE_1__* operands; } ;
struct TYPE_3__ {int postind; int writeback; int /*<<< orphan*/  preind; int /*<<< orphan*/  isreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  constraint (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  encode_arm_addr_mode_2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__ inst ; 

__attribute__((used)) static void
do_pld (void)
{
  constraint (!inst.operands[0].isreg,
	      _("'[' expected after PLD mnemonic"));
  constraint (inst.operands[0].postind,
	      _("post-indexed expression used in preload instruction"));
  constraint (inst.operands[0].writeback,
	      _("writeback used in preload instruction"));
  constraint (!inst.operands[0].preind,
	      _("unindexed addressing used in preload instruction"));
  encode_arm_addr_mode_2 (0, /*is_t=*/FALSE);
}