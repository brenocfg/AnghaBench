#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct edge_prediction {int ep_probability; int ep_predictor; TYPE_1__* ep_edge; struct edge_prediction* ep_next; } ;
typedef  enum br_predictor { ____Placeholder_br_predictor } br_predictor ;
typedef  TYPE_1__* edge ;
struct TYPE_5__ {struct edge_prediction* predictions; int /*<<< orphan*/  succs; } ;
struct TYPE_4__ {TYPE_3__* src; } ;

/* Variables and functions */
 int EDGE_COUNT (int /*<<< orphan*/ ) ; 
 TYPE_3__* ENTRY_BLOCK_PTR ; 
 scalar_t__ PROFILE_GUESSED ; 
 scalar_t__ flag_guess_branch_prob ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 struct edge_prediction* ggc_alloc (int) ; 
 scalar_t__ optimize ; 
 scalar_t__ profile_status ; 

void
tree_predict_edge (edge e, enum br_predictor predictor, int probability)
{
  gcc_assert (profile_status != PROFILE_GUESSED);
  if ((e->src != ENTRY_BLOCK_PTR && EDGE_COUNT (e->src->succs) > 1)
      && flag_guess_branch_prob && optimize)
    {
      struct edge_prediction *i = ggc_alloc (sizeof (struct edge_prediction));

      i->ep_next = e->src->predictions;
      e->src->predictions = i;
      i->ep_probability = probability;
      i->ep_predictor = predictor;
      i->ep_edge = e;
    }
}