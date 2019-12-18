#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* pattern_seq ;
struct TYPE_4__ {struct TYPE_4__* next_pattern_seq; int /*<<< orphan*/  link_reg; } ;

/* Variables and functions */
 size_t REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  determine_seq_blocks () ; 
 int /*<<< orphan*/  erase_matching_seqs () ; 
 int /*<<< orphan*/  free_pattern_seq (TYPE_1__*) ; 
 int /*<<< orphan*/  free_seq_blocks () ; 
 TYPE_1__* pattern_seqs ; 
 int* regs_ever_live ; 
 int /*<<< orphan*/  split_blocks_after_seqs () ; 
 int /*<<< orphan*/  split_pattern_seq () ; 

__attribute__((used)) static void
abstract_best_seq (void)
{
  pattern_seq bestpseq;

  /* Do the abstraction.  */
  determine_seq_blocks ();
  split_blocks_after_seqs ();
  split_pattern_seq ();
  erase_matching_seqs ();
  free_seq_blocks ();

  /* Record the usage of the link register.  */
  regs_ever_live[REGNO (pattern_seqs->link_reg)] = 1;

  /* Remove the best pattern sequence.  */
  bestpseq = pattern_seqs;
  pattern_seqs = bestpseq->next_pattern_seq;
  free_pattern_seq (bestpseq);
}