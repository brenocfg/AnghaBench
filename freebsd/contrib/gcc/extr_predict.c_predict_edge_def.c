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
typedef  enum prediction { ____Placeholder_prediction } prediction ;
typedef  enum br_predictor { ____Placeholder_br_predictor } br_predictor ;
typedef  int /*<<< orphan*/  edge ;
struct TYPE_2__ {int hitrate; } ;

/* Variables and functions */
 int REG_BR_PROB_BASE ; 
 int TAKEN ; 
 int /*<<< orphan*/  predict_edge (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* predictor_info ; 

void
predict_edge_def (edge e, enum br_predictor predictor,
		  enum prediction taken)
{
   int probability = predictor_info[(int) predictor].hitrate;

   if (taken != TAKEN)
     probability = REG_BR_PROB_BASE - probability;

   predict_edge (e, predictor, probability);
}