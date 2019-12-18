#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pattern_seq ;
typedef  TYPE_2__* matching_seq ;
struct TYPE_5__ {scalar_t__ cost; int /*<<< orphan*/  abstracted_length; int /*<<< orphan*/  insn; struct TYPE_5__* next_matching_seq; } ;
struct TYPE_4__ {struct TYPE_4__* next_pattern_seq; int /*<<< orphan*/  abstracted_length; int /*<<< orphan*/  insn; TYPE_2__* matching_seqs; } ;

/* Variables and functions */
 int /*<<< orphan*/  erase_from_pattern_seqs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* pattern_seqs ; 
 scalar_t__ seq_call_cost ; 

__attribute__((used)) static void
update_pattern_seqs (void)
{
  pattern_seq bestpseq;
  matching_seq mseq;

  bestpseq = pattern_seqs;
  pattern_seqs = bestpseq->next_pattern_seq;

  for (mseq = bestpseq->matching_seqs; mseq; mseq = mseq->next_matching_seq)
    if (mseq->cost > seq_call_cost)
      erase_from_pattern_seqs (mseq->insn, mseq->abstracted_length);
  erase_from_pattern_seqs (bestpseq->insn, bestpseq->abstracted_length);

  bestpseq->next_pattern_seq = pattern_seqs;
  pattern_seqs = bestpseq;
}