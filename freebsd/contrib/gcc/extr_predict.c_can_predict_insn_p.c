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
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int /*<<< orphan*/  succs; } ;

/* Variables and functions */
 TYPE_1__* BLOCK_FOR_INSN (int /*<<< orphan*/ ) ; 
 int EDGE_COUNT (int /*<<< orphan*/ ) ; 
 scalar_t__ JUMP_P (int /*<<< orphan*/ ) ; 
 scalar_t__ any_condjump_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
can_predict_insn_p (rtx insn)
{
  return (JUMP_P (insn)
	  && any_condjump_p (insn)
	  && EDGE_COUNT (BLOCK_FOR_INSN (insn)->succs) >= 2);
}