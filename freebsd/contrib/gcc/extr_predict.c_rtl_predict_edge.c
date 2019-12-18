#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  enum br_predictor { ____Placeholder_br_predictor } br_predictor ;
typedef  TYPE_1__* edge ;
struct TYPE_3__ {int flags; int /*<<< orphan*/  src; } ;

/* Variables and functions */
 int /*<<< orphan*/  BB_END (int /*<<< orphan*/ ) ; 
 int EDGE_FALLTHRU ; 
 int REG_BR_PROB_BASE ; 
 int /*<<< orphan*/  any_condjump_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  predict_insn (int /*<<< orphan*/ ,int,int) ; 

void
rtl_predict_edge (edge e, enum br_predictor predictor, int probability)
{
  rtx last_insn;
  last_insn = BB_END (e->src);

  /* We can store the branch prediction information only about
     conditional jumps.  */
  if (!any_condjump_p (last_insn))
    return;

  /* We always store probability of branching.  */
  if (e->flags & EDGE_FALLTHRU)
    probability = REG_BR_PROB_BASE - probability;

  predict_insn (last_insn, predictor, probability);
}